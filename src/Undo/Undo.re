open Types;
open Belt;

let undoExistingMove = (prev, next, card, location) =>
  switch (prev, next, card) {
  /* Take all cards from stock, flip, & put in hand */
  | (Hand, Stock, None) =>
    let {stock, hand} = location;
    let nextHand =
      stock
      ->List.reverse
      ->List.mapWithIndex((i, c) =>
          {...c, faceUp: true, selectable: i == 0}
        );

    {...location, hand: nextHand, stock: []};
  /* Take first 3 of hand, flip, & put in stock  */
  | (Stock, Hand, None) =>
    let {stock, hand} = location;

    let flipCard = card => {...card, faceUp: false, selectable: false};
    let flipCards = cards => List.map(cards, flipCard);
    let prepareStock = cards => flipCards(cards)->List.concat(stock);

    let (nextStock, nextHand) =
      switch (hand) {
      | [] => (stock, hand)
      | [a] => (flipCards([a]), [])
      | [a, b] => (prepareStock([b, a]), [])
      | [a, b, c] => (prepareStock([c, b, a]), [])
      | [a, b, c, d, ...rest] => (
          prepareStock([c, b, a]),
          [{...d, selectable: true}, ...rest],
        )
      };

    {...location, hand: nextHand, stock: nextStock};
  /* Take whatever _card_ is at the top of the foundation row, remove from foundation, and add back to tableau row */
  | (Tableau(prevT), Foundation(nextF), Some(card)) => location
  /* Take _card_ from foundation row, add back to top of hand  */
  | (Hand, Foundation(nextF), Some(card)) => location
  /* Take _card_ from tableau row & apply to foundation row */
  | (Foundation(prevF), Tableau(nextT), Some(card)) => location
  /* Take card from tableau row & drop @ beginning of hand */
  | (Hand, Tableau(nextT), Some(card)) => location
  /* Take card from one tableau row & add it to the other. */
  | (Tableau(prevT), Tableau(nextT), Some(card)) => location
  | _ => location
  };

let undoMove = ({prev, next, card}, location) =>
  switch (prev, next, card) {
  | (Some(previousLocation), Some(nextLocation), card) =>
    undoExistingMove(previousLocation, nextLocation, card, location)
  | _ => location
  };