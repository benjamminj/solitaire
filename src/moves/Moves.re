/**
 * Game moves, validation, & other logic
 */
open Types;

let isOppositeSuit = (card, destinationCard) =>
  switch (card.suit) {
  | Hearts
  | Diamonds => destinationCard.suit == Clubs || destinationCard.suit == Spades
  | Clubs
  | Spades =>
    destinationCard.suit == Hearts || destinationCard.suit == Diamonds
  };

let validateMoveToTableau = (~card, ~destination): bool =>
  switch (destination) {
  | [bottomCard, ..._rest] =>
    isOppositeSuit(card, bottomCard) && card.rank == bottomCard.rank - 1
  | [] => card.rank == 13 /* Kings only on empty tableau rows */
  };

let validateMoveToFoundation = (~card, ~destination): bool =>
  switch (destination) {
  | [topCard, ..._rest] =>
    card.suit == topCard.suit && card.rank == topCard.rank + 1
  | [] => card.rank == 1 /* Aces only on empty foundation rows  */
  };

let addCard = (card, list) => [card, ...list];
let filterOutCard = card => List.filter(item => item.id != card.id);

let getListPlusCard = (card, row, arr) => {
  let copy = Array.copy(arr);

  copy[row] = addCard(card, copy[row]);

  copy;
};

let getListWithoutCard = (card, row, arr) => {
  let copy = Array.copy(arr);

  /* Only remove the card from the row that was designated. */
  copy[row] = filterOutCard(card, copy[row]);

  copy;
};

let flipLastCard = list =>
  switch (list) {
  | [bottomCard, ...rest] => [
      {...bottomCard, selectable: true, faceUp: true},
      ...rest,
    ]
  | [] => list
  };

let makeFirstCardSelectable = list =>
  switch (list) {
  | [first, ...rest] => [{...first, selectable: true}, ...rest]
  | [] => []
  };

let splitAt = (item, list) => {
  let rec search = (list, result) =>
    switch (list) {
    | [a, ...rest] when a == item => (List.append(result, [a]), rest)
    | [a, ...rest] => search(rest, List.append(result, [a]))
    | _ => (list, result)
    };

  search(list, []);
};

let getUpdatedLocation = (~prevLocation, ~nextLocation, ~card, ~location) => {
  let filterOutCard = filterOutCard(card);

  switch (prevLocation, nextLocation) {
  | (Tableau(rowT), Foundation(rowF)) =>
    let {foundation, tableau} = location;
    let isValid =
      validateMoveToFoundation(~card, ~destination=foundation[rowF]);

    let flipLastCardInPrevRow = arr => {
      let copy = Array.copy(arr);

      let list = copy[rowT];
      copy[rowT] = flipLastCard(list);

      copy;
    };

    let tableauMinusCard =
      isValid ?
        getListWithoutCard(card, rowT, tableau) |> flipLastCardInPrevRow :
        tableau;
    let foundationPlusCard =
      isValid ? getListPlusCard(card, rowF, foundation) : foundation;

    (
      {...location, foundation: foundationPlusCard, tableau: tableauMinusCard},
      isValid,
    );
  | (Hand, Foundation(rowF)) =>
    let {hand, foundation} = location;
    let isValid =
      validateMoveToFoundation(~card, ~destination=foundation[rowF]);
    /**
     * Remove the card from the hand & add to tableau.
     * Once there is validation set up around _which_ cards in the hand can be selected we
     * can get rid of the `filterOutCard` function and just grab from the head of the list
     */
    let handMinusCard =
      isValid ? filterOutCard(hand) |> makeFirstCardSelectable : hand;
    let foundationPlusCard =
      isValid ? getListPlusCard(card, rowF, foundation) : foundation;

    (
      {...location, hand: handMinusCard, foundation: foundationPlusCard},
      isValid,
    );
  | (Foundation(rowF), Tableau(rowT)) =>
    let {foundation, tableau} = location;
    let isValid = validateMoveToTableau(~card, ~destination=tableau[rowT]);

    let foundationMinusCard =
      isValid ? getListWithoutCard(card, rowF, foundation) : foundation;
    let tableauPlusCard =
      isValid ? getListPlusCard(card, rowT, tableau) : tableau;

    (
      {...location, tableau: tableauPlusCard, foundation: foundationMinusCard},
      isValid,
    );
  | (Tableau(rowPrev), Tableau(rowNext)) =>
    let {tableau} = location;
    let isValid = validateMoveToTableau(~card, ~destination=tableau[rowNext]);

    let (cardsToMove, rest) = splitAt(card, tableau[rowPrev]);

    let updateSelection = (i, list) =>
      switch (i) {
      | i when i == rowPrev && i == rowNext => list
      | i when i == rowPrev => flipLastCard(rest)
      | i when i == rowNext => List.append(cardsToMove, list)
      | _ => list
      };

    let next = isValid ? Array.mapi(updateSelection, tableau) : tableau;

    ({...location, tableau: next}, isValid);
  | (Hand, Tableau(row)) =>
    let {hand, tableau} = location;
    let isValid = validateMoveToTableau(~card, ~destination=tableau[row]);

    let handMinusCard =
      isValid ? filterOutCard(hand) |> makeFirstCardSelectable : hand;
    let tableauPlusCard =
      isValid ? getListPlusCard(card, row, tableau) : tableau;
    ({...location, tableau: tableauPlusCard, hand: handMinusCard}, isValid);
  | _ => (location, false)
  };
};