/* type cardList = list(card); */
open Types;

type location = {
  foundation: array(cardList),
  tableau: array(cardList),
  stock: cardList,
  hand: cardList,
};

type state = {location};

type action =
  | MoveCard
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

let make = _children => {
  ...component,
  initialState: () => {
    location: {
      foundation: [||],
      tableau: [||],
      stock: [],
      hand: [],
    },
  },
  reducer: (action, state) =>
    switch (action) {
    | Init =>
      let (tableau, stock) = generateDeck() |> shuffleDeck |> dealCards;

      ReasonReact.Update({
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
        | [] => ([], hand)
        | [a] => ([a, ...hand], [])
        | [a, b] => ([a, b, ...hand], [])
        | [a, b, c, ...rest] => ([a, b, c, ...hand], rest)
        };

      ReasonReact.Update({
        location: {
          ...state.location,
          hand: nextHand,
          stock: rest,
        },
      });
    | MoveCard => ReasonReact.Update(state)
    },
  render: self =>
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
              <CardStack cards=[|self.state.location.hand|] />
            </pre>
            <pre style=rowStyle>
              /* { TODO -- uncomment when ready to only show the top item & we know that all the actions are working
                   let {stock} = self.state.location;

                   switch (List.hd(stock)) {
                   | card =>
                     <Card id={card.id} rank={card.rank} suit={card.suit} />
                   | exception _err => ReasonReact.null
                   };
                 } */

                <div> {ReasonReact.string("stock")} </div>
                <CardStack cards=[|self.state.location.stock|] />
              </pre>
          </>;
        }
      </div>
      /* Tableau component */
      <pre style={ReactDOMRe.Style.make(~display="flex", ())}>
        <CardStack cards={self.state.location.tableau} />
      </pre>
    </>,
};