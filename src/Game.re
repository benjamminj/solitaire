/* type cardList = list(card); */
open Types;

type location = {
  foundation: array(cardList),
  tableau: array(cardList),
  stock: cardList,
  hand: cardList,
};

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

let getUpdatedLocationFromMoves =
    (~prevLocation, ~nextLocation, ~card, ~state) => {
  let _placeholder = "test";

  /*
   * Adds the card to a designated row in the foundation
   * Later, when we add validation, can likely simply take validation as a parameterized fn.
   */
  let getListPlusCard = (arr, row) => {
    let copy = Array.copy(arr);
    let addCard = List.append([card]);

    copy[row] = addCard(copy[row]);

    copy;
  };

  let filterOutCard = List.filter(item => item.id != card.id);
  /* Remove a card from a list */
  let getListWithoutCard = (arr, row) => {
    let copy = Array.copy(arr);

    /* Only remove the card from the row that was designated. */
    copy[row] = filterOutCard(copy[row]);

    copy;
  };

  /** 
   * NOTE -- still need to add validation, however, this logic is starting to get a bit verbose.
   * It might be best to break this out into a separate module to keep this part of the app more lean
   */
  switch (prevLocation, nextLocation) {
  | (Tableau(rowT), Foundation(rowF)) =>
    let {foundation, tableau} = state.location;

    let tableauMinusCard = getListWithoutCard(tableau, rowT);
    let foundationPlusCard = getListPlusCard(foundation, rowF);

    {...state.location, foundation: foundationPlusCard, tableau: tableauMinusCard};
  | (Hand, Foundation(rowF)) =>
    let {hand, foundation} = state.location;
    /**
     * Remove the card from the hand & add to tableau.
     * Once there is validation set up around _which_ cards in the hand can be selected we
     * can get rid of the `filterOutCard` function and just grab from the head of the list
     */
    let handMinusCard = filterOutCard(hand);
    let foundationPlusCard = getListPlusCard(foundation, rowF);

    {...state.location, hand: handMinusCard, foundation: foundationPlusCard};
  | (Foundation(rowF), Tableau(rowT)) =>
    let {foundation, tableau} = state.location;

    let foundationMinusCard = getListWithoutCard(foundation, rowF);
    let tableauPlusCard = getListPlusCard(tableau, rowT);

    {
      ...state.location,
      tableau: tableauPlusCard,
      foundation: foundationMinusCard,
    };
  | (Tableau(rowPrev), Tableau(rowNext)) =>
    let {tableau} = state.location;

    let updateSelection = (i, list) =>
      switch (i) {
      | i when i == rowPrev && i == rowNext => list
      | i when i == rowPrev => List.filter(item => item.id != card.id, list)
      | i when i == rowNext => List.append([card], list)
      | _ => list
      };

    let next = Array.mapi(updateSelection, tableau);
    Js.log("here");

    {...state.location, tableau: next};
  | (Hand, Tableau(row)) =>
    let {hand, tableau} = state.location;
    let handMinusCard = filterOutCard(hand);
    let tableauPlusCard = getListPlusCard(tableau, row);
    {...state.location, tableau: tableauPlusCard, hand: handMinusCard};
  | _ => state.location
  };
};

/* STATE */
let initialState = {
  location: {
    foundation: [|[], [], [], []|],
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

/* COMPONENT */
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
      let location =
        switch (prev, next, card) {
        | (Some(prevLocation), Some(nextLocation), Some(card)) =>
          getUpdatedLocationFromMoves(
            ~prevLocation,
            ~nextLocation,
            ~card,
            ~state,
          )
        | _ => state.location
        };
      /**
       * TODO -- add all the validation logic to move a card from its previous
       * location to its next location, or cancel if invalid
       * In the future, to introduce the ability to undo a move, will need to add
       * a new move to an array of moves rather than just clearing it out.
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
      <div style={ReactDOMRe.Style.make(~display="flex", ())}>
        {
          let rowStyle = ReactDOMRe.Style.make(~padding="0 0.25rem", ());
          let flex = ReactDOMRe.Style.make(~display="flex", ());
          <>
            <pre style=rowStyle>
              <div>
                {ReasonReact.string("foundation")}
                <div style=flex>
                  <CardStack
                    cards={self.state.location.foundation}
                    onClickCard={i => onClickCard(~location=Foundation(i))}
                  />
                </div>
              </div>
            </pre>
            <pre style=rowStyle>
              <div> {ReasonReact.string("hand")} </div>
              /* {
                     /* For now, leave this here. We can uncomment once game mechanics are working */
                   let {hand} = self.state.location;

                   let displayedCards =
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