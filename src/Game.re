/* type cardList = list(card); */
open Types;

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
    List.map(
      rank => {
        id: idPrefix * 100 + rank,
        suit,
        rank,
        selectable: false,
        faceUp: false,
      },
      ranks,
    );
  };

  let suits = [Hearts, Diamonds, Clubs, Spades];

  suits |> List.mapi(generateSuit) |> List.flatten;
};

let shuffleDeck = (deck: list(card)): list(card) => {
  let arr = Array.(deck |> of_list |> copy);

  let start = Array.length(arr) - 1;

  for (i in start downto 1) {
    let temp = arr[i];

    /*
     * In order to get actual random data, we need to seed Random with something that isn't
     * deterministic.
     * NOTE -- likely can move this further up in the call tree & inject
     */
    let seed = Js.Date.now();
    Random.init(int_of_float(seed));

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
    |> (
      arr => {
        let start = ref(0);

        Array.init(
          7,
          i => {
            let amt = i + 1;
            let nextStart = start^ + amt;
            let items = Array.sub(arr, start^, amt);
            items[0] = {...items[0], faceUp: true, selectable: true};

            start := nextStart;
            items |> Array.to_list;
          },
        );
      }
    );

  (tableau, Array.to_list(stock));
};

let getNextMove = (updater, state, ~location, ~card: option(card)) => {
  let {moveKey, move} = state;

  switch (moveKey) {
  | Prev => updater(UpdateMove({prev: Some(location), next: None, card}))
  | Next => updater(MoveCard({...move, next: Some(location)}))
  };
};

/* STYLES */
module Styles = {
  open Css;
  open Global.Styles;

  let container =
    style([maxWidth @@ rem(25.0), margin2(~v=`zero, ~h=`auto)]);

  let grid =
    style([
      display @@ `grid,
      `declaration(("gridTemplateColumns", "repeat(7, 1fr)")),
      gridTemplateRows @@ [cardHeight, auto],
      gridRowGap @@ rem(1.0),
      gridColumnGap @@ rem(0.25),
    ]);
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
      Js.log("deal hand");
      let prepareHand = (listA, listB) => {
        /* Flip all the cards in listA */
        let flippedListA =
          List.mapi(
            (i, card) => {...card, faceUp: true, selectable: i == 0},
            listA,
          );
        List.append(flippedListA, listB);
      };

      let prepareStock = list =>
        List.rev_map(
          card => {...card, faceUp: false, selectable: false},
          list,
        );

      let (nextHand, rest) =
        switch (stock) {
        /* NOTE -- move all of hand back into stock. Will need to add logic when limiting the number of deals */
        | [] => ([], prepareStock(hand))
        | [a] => (prepareHand([a], hand), [])
        | [a, b] => (prepareHand([b, a], hand), [])
        | [a, b, c, ...rest] => (prepareHand([c, b, a], hand), rest)
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
          Moves.getUpdatedLocation(
            ~prevLocation,
            ~nextLocation,
            ~card,
            ~state,
          )
        | _ => state.location
        };
      ReasonReact.Update({
        location,
        move: initialState.move,
        moveKey: initialState.moveKey,
      });
    },
  render: self => {
    let onClickCard = getNextMove(self.send, self.state);
    <div className=Styles.container>
      <div>
        <button onClick={_ev => self.send(Init)}>
          {ReasonReact.string("init")}
        </button>
      </div>
      <div className=Styles.grid>
        <Foundation rows={self.state.location.foundation} onClickCard />
        <div className=Css.(style([gridColumn(5, 7)]))>
          <Hand onClickCard hand={self.state.location.hand} />
        </div>
        <Stock
          cards={self.state.location.stock}
          onClick={() => self.send(DealHand)}
        />
        <Tableau
          rows={self.state.location.tableau}
          onClickCard={i => onClickCard(~location=Tableau(i))}
        />
      </div>
    </div>;
  },
};