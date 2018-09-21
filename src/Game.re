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

/* NOTE -- can likely be made more testable, will need to remove the reliance on "self" */
let getNextMove = (self, ~location, ~card: option(card)) => {
  open ReasonReact;
  let {moveKey, move} = self.state;

  switch (moveKey) {
  | Prev =>
    Js.log2("set previous", location);
    self.send(UpdateMove({prev: Some(location), next: None, card}));
  | Next =>
    Js.log2("set next", location);
    self.send(MoveCard({...move, next: Some(location)}));
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
                  {
                    self.state.location.foundation
                    |> Array.mapi((i, row) =>
                         <div
                           className=Css.(
                             style([
                               margin3(
                                 ~top=rem(0.25),
                                 ~h=rem(0.25),
                                 ~bottom=`zero,
                               ),
                             ])
                           )>
                           {
                             switch (row) {
                             | [] =>
                               <EmptyCard
                                 key={"empty-" ++ string_of_int(i)}
                                 onClick=(
                                   _ev =>
                                     onClickCard(
                                       ~location=Foundation(i),
                                       ~card=None,
                                     )
                                 )
                               />
                             | [card, ..._rest] =>
                               <Card
                                 key={string_of_int(card.id)}
                                 card
                                 onClick=(
                                   (~card) =>
                                     onClickCard(
                                       ~location=Foundation(i),
                                       ~card=Some(card),
                                     )
                                 )
                               />
                             }
                           }
                         </div>
                       )
                    |> ReasonReact.array
                  }
                </div>
              </div>
            </pre>
            <pre style=rowStyle>
              <div> {ReasonReact.string("hand")} </div>
              {
                let {hand} = self.state.location;

                let displayedCards =
                  switch (hand) {
                  | [] => []
                  | [a] => [a]
                  | [a, b] => [a, b]
                  | [a, b, c, ..._rest] => [a, b, c]
                  };
                <CardStack
                  styles=Css.[flexDirection(`row)]
                  cards=displayedCards
                  direction=Horizontal
                  onClickCard={(~card) => onClickCard(~location=Hand, ~card)}
                />;
              }
            </pre>
            <pre style=rowStyle>
              <div> {ReasonReact.string("stock")} </div>
              <div className={Css.(style([marginTop(rem(0.25))]))}>
              {
                let {stock} = self.state.location;

                switch (stock) {
                | [] => <EmptyCard onClick=(_ev => self.send(DealHand)) />
                | [card, ..._rest] =>
                  <Card
                    card={...card, selectable: true}
                    onClick=((~card as _c) => self.send(DealHand))
                  />
                };
              }
              </div>
            </pre>
          </>;
        }
      </div>
      /* Tableau component */
      <pre style={ReactDOMRe.Style.make(~display="flex", ())}>
        <Tableau
          rows={self.state.location.tableau}
          onClickCard={(i) => onClickCard(~location=Tableau(i))}
        />
      </pre>
    </>;
  },
};