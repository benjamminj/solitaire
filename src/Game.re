type suit =
  | Hearts
  | Diamonds
  | Clubs
  | Spades;

type card = {
  id: int,
  suit,
  rank: int,
};

type cardList = list(card);
type location = {
  foundation: array(cardList),
  tableau: array(cardList),
  stock: cardList,
  hand: cardList,
};

type state = {
  cards: cardList,
  location,
};

type action =
  | MoveCard
  | Shuffle
  | DealCards
  | GenerateList;

let component = ReasonReact.reducerComponent("Game");

/* Utilities */
let generateDeck = (): list(card) => {
  let generateSuit = (idPrefix, suit: suit): list(card) => {
    let ranks = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13];
    List.map(rank => {id: idPrefix + rank, suit, rank}, ranks);
  };

  let suits = [Hearts, Diamonds, Clubs, Spades];
  /* let suitCards = list_of_array(Array.mapi(generateSuit, suits)); */
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

let make = _children => {
  ...component,
  initialState: () => {
    cards: generateDeck(),
    location: {
      foundation: [||],
      tableau: [||],
      stock: [],
      hand: [],
    },
  },
  reducer: (action, state) =>
    switch (action) {
    | MoveCard => ReasonReact.Update({...state, cards: []})
    | GenerateList => ReasonReact.Update({...state, cards: generateDeck()})
    | Shuffle =>
      ReasonReact.Update({...state, cards: shuffleDeck(state.cards)})
    | DealCards =>
      let {cards} = state;
      let (cardsToDeal, stock) =
        Array.(
          cards
          |> of_list
          |> (arr => (sub(arr, 0, 28), sub(arr, 28, length(arr) - 28)))
        );

      /**
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
      let location = {
        ...state.location,
        tableau,
        stock: stock |> Array.to_list,
      };

      ReasonReact.Update({...state, location});
    },
  render: self =>
    <>
      <div>
        <button onClick={_ev => self.send(Shuffle)}>
          {ReasonReact.string("shuffle")}
        </button>
        <button onClick={_ev => self.send(DealCards)}>
          {ReasonReact.string("deal")}
        </button>
      </div>
      /* Tableau component */
      <pre style={ReactDOMRe.Style.make(~display="flex", ())}>
        ...{
             self.state.location.tableau
             |> Array.map(cardList =>
                  <div
                    style={
                      ReactDOMRe.Style.make(
                        ~display="flex",
                        ~flexDirection="column",
                        ~padding="0.25rem",
                        (),
                      )
                    }>
                    ...{
                         cardList
                         |> List.map(card =>
                              <div>
                                <span
                                  style={
                                    ReactDOMRe.Style.make(
                                      ~marginRight="0.25rem",
                                      (),
                                    )
                                  }>
                                  {
                                    ReasonReact.string(
                                      string_of_int(card.rank),
                                    )
                                  }
                                </span>
                                <span>
                                  {
                                    (
                                      switch (card.suit) {
                                      | Hearts => "hearts"
                                      | Diamonds => "diamonds"
                                      | Clubs => "clubs"
                                      | Spades => "spades"
                                      }
                                    )
                                    |> ReasonReact.string
                                  }
                                </span>
                              </div>
                            )
                         |> Array.of_list
                       }
                  </div>
                )
           }
      </pre>
    </>,
};