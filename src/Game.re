/* type cardList = list(card); */
open Types;

type location = {
  foundation: array(cardList),
  tableau: array(cardList),
  stock: cardList,
  hand: cardList,
};

/* TODO -- add args to the ones that require a row */
type locationKey =
  | Foundation(int)
  | Tableau(int)
  | Stock
  | Hand;

type move = {
  prev: option(locationKey),
  next: option(locationKey),
  card: option(card),
};

type moveKey =
  | Prev
  | Next;

type state = {
  location,
  move,
  moveKey,
};

type action =
  | UpdateMove(move)
  | MoveCard(move)
  | DealHand
  | Init;

let component = ReasonReact.reducerComponent("Game");

/* Utilities */
let generateDeck = (): list(card) => {
  let generateSuit = (idPrefix, suit: suit): list(card) => {
    let ranks = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13];
    List.map(rank => {id: idPrefix * 100 + rank, suit, rank}, ranks);
  };

  let suits = [Hearts, Diamonds, Clubs, Spades];

  suits |> List.mapi(generateSuit) |> List.flatten;
};

let shuffleDeck = (deck: list(card)): list(card) => {
  let arr = Array.(deck |> of_list |> copy);

  let start = Array.length(arr) - 1;

  for (i in start downto 1) {
    let temp = arr[i];
    let random =
      Random.float(1.0) *. float_of_int(i - 1) |> floor |> int_of_float;

    arr[i] = arr[random];
    arr[random] = temp;
  };

  Array.to_list(arr);
};

let dealCards = cards => {
  let (cardsToDeal, stock) =
    Array.(
      cards
      |> of_list
      |> (arr => (sub(arr, 0, 28), sub(arr, 28, length(arr) - 28)))
    );

  /*
   * Go thru the array of cards to deal & assign the number of cards per row equal to the row number
   * Perhaps for now don't do a "true" deal, where each row recieves 1 card at a time until the 7th is filled.
   */
  let tableau: array(cardList) =
    cardsToDeal
    /* |> Array.to_list */
    |> (
      arr => {
        let start = ref(0);

        Array.init(
          7,
          i => {
            let amt = i + 1;
            let nextStart = start^ + amt;
            let items = Array.sub(arr, start^, amt);

            start := nextStart;
            items |> Array.to_list;
          },
        );
      }
    );

  (tableau, Array.to_list(stock));
};

let getNextMove = (self, ~location, ~card: option(card)) => {
  let {moveKey, move} = self.ReasonReact.state;

  switch (moveKey) {
  | Prev =>
    Js.log("set previous");
    self.ReasonReact.send(
      UpdateMove({prev: Some(location), next: None, card}),
    );
  | Next =>
    Js.log("set next");
    self.ReasonReact.send(MoveCard({...move, next: Some(location)}));
  };
};

let initialState = {
  location: {
    foundation: [||],
    tableau: [||],
    stock: [],
    hand: [],
  },
  move: {
    prev: None,
    next: None,
    card: None,
  },
  moveKey: Prev,
};

let make = _children => {
  ...component,
  initialState: () => initialState,
  reducer: (action, state) =>
    switch (action) {
    | Init =>
      let (tableau, stock) = generateDeck() |> shuffleDeck |> dealCards;

      ReasonReact.Update({
        ...state,
        location: {
          ...state.location,
          tableau,
          stock,
        },
      });
    | DealHand =>
      /* Go grab the first 3 from the list */
      let {stock, hand} = state.location;
      let (nextHand, rest) =
        switch (stock) {
        /* NOTE -- move all of hand back into stock. Will need to add logic when limiting the number of deals */
        | [] => ([], List.rev(hand))
        | [a] => ([a, ...hand], [])
        | [a, b] => ([b, a, ...hand], [])
        | [a, b, c, ...rest] => ([c, b, a, ...hand], rest)
        };

      ReasonReact.Update({
        ...state,
        location: {
          ...state.location,
          hand: nextHand,
          stock: rest,
        },
      });
    | UpdateMove(move) => ReasonReact.Update({...state, move, moveKey: Next})
    | MoveCard({prev, next, card}) =>
      let getUpdatedLocationFromMoves = (prevLocation, nextLocation, card) =>
        switch (prevLocation, nextLocation) {
        | (_, Foundation(row)) =>
          /* TODO --
           * add logic & validation for adding an item to a foundation row
           * in addition, will need to add some click areas inside foundation to allow it to actually be clicked
           */
          let {foundation} = state.location;

          let updateSelection = (i, list) =>
            i == row ? List.append(list, [card]) : list;
          let next = Array.mapi(updateSelection, foundation);

          {...state.location, foundation: next};
        /* TODO -- add logic & validation for moving card from foundation to tableau */
        | (Foundation(rowF), Tableau(rowT)) => state.location
        | (Tableau(rowPrev), Tableau(rowNext)) =>
          /* NOTE -- add logic & validation for moving a card from tableau to ttableau row */
          let {tableau} = state.location;

          /* TODO -- see if there's a cleaner or simpler way to do this...might be imperative? */
          let updateSelection = (i, list) =>
            switch (i) {
            | i when i == rowPrev && i == rowNext => list
            | i when i == rowPrev =>
              List.filter(item => item.id != card.id, list)
            | i when i == rowNext => List.append([card], list)
            | _ => list
            };

          let next = Array.mapi(updateSelection, tableau);
          Js.log("here");

          {...state.location, tableau: next};
        /* TODO -- move the card from the hand to the tableau */
        | (Hand, Tableau(row)) => state.location
        | _ => state.location
        };

      let location =
        switch (prev, next, card) {
        | (Some(prevLocation), Some(nextLocation), Some(card)) =>
          getUpdatedLocationFromMoves(prevLocation, nextLocation, card)
        | _ => state.location
        };
      /**
       * TODO -- add all the validation logic to move a card from its previous
       * location to its next location, or cancel if invalid
       */
      /**
       * expose a callback that configures with an arg as to _what_ key in the next move it updates
       * store that key in state...when adding the "prev" key (i.e.) clicking on a card,
       * it will add the "prev" & the "card" to the next move. This also makes it easier to
       * highlight the card in an active state
       *
       * _THEN_ the next click will take the same callback and trigger an action to modify the "next" location
       * Then it will apply this action to actually move the card with the current action.
       * In addition, it will clear out the move. Later on, it could also pop an empty move onto the stack of moves.
       */
      ReasonReact.Update({
        location,
        move: initialState.move,
        moveKey: initialState.moveKey,
      });
    },
  render: self => {
    let onClickCard = getNextMove(self);
    <>
      <div>
        <button onClick={_ev => self.send(Init)}>
          {ReasonReact.string("init")}
        </button>
        <button onClick={_ev => self.send(DealHand)}>
          {ReasonReact.string("deal hand")}
        </button>
      </div>
      /* Foundation placeholder */
      <div style={ReactDOMRe.Style.make(~display="flex", ())}>
        {
          let rowStyle = ReactDOMRe.Style.make(~padding="0 0.25rem", ());

          <>
            <pre style=rowStyle> {ReasonReact.string("foundation")} </pre>
            <pre style=rowStyle>
              <div> {ReasonReact.string("hand")} </div>
              /* {
                   let {hand} = self.state.location;

                   let displayedCards =
                     /* TODO -- see if there's a better way to elegantly supply this logic */
                     switch (hand) {
                     | [] => []
                     | [a] => [a]
                     | [a, b] => [a, b]
                     | [a, b, c, ..._rest] => [a, b, c]
                     };

                   <CardStack cards=[|displayedCards|] />;
                 } */
              <CardStack
                cards=[|self.state.location.hand|]
                onClickCard={_i => onClickCard(~location=Hand)}
              />
            </pre>
            <pre style=rowStyle>
              <div> {ReasonReact.string("stock")} </div>
              /* {
                   let {stock} = self.state.location;

                   switch (List.hd(stock)) {
                   | card =>
                     <Card id={card.id} rank={card.rank} suit={card.suit} />
                   | exception _err => ReasonReact.null
                   };
                 } */
              <CardStack
                cards=[|self.state.location.stock|]
                onClickCard={_i => onClickCard(~location=Stock)}
              />
            </pre>
          </>;
        }
      </div>
      /* Tableau component */
      <pre style={ReactDOMRe.Style.make(~display="flex", ())}>
        /* TODO -- make sure that the arguments get assigned to the correct row? */

          <CardStack
            cards={self.state.location.tableau}
            onClickCard={i => onClickCard(~location=Tableau(i))}
          />
        </pre>
    </>;
  },
};