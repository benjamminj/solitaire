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

type state = {cards: list(card)};

type action =
  | MoveCard
  | Shuffle
  | GenerateList;

let component = ReasonReact.reducerComponent("Game");

/* Utilities */
let generateDeck = () : list(card) => {
  let generateSuit = (idPrefix, suit: suit) : list(card) => {
    let ranks = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13];
    List.map(rank => {id: idPrefix + rank, suit, rank}, ranks);
  };

  let suits = [Hearts, Diamonds, Clubs, Spades];
  /* let suitCards = list_of_array(Array.mapi(generateSuit, suits)); */
  suits |> List.mapi(generateSuit) |> List.flatten;
};

let shuffleDeck = (deck: list(card)) : list(card) => {
  let [head, ...tail] = deck;
  let copy = [head, ...tail];

  let arr = Array.of_list(copy);

  let start = Array.length(arr) - 1;
  for (i in start downto 1) {
    let temp = arr[i];
    let random = Random.float(1.0) *. float_of_int(i - 1) |> floor |> int_of_float;
    Js.log((random, temp, i));

    arr[i] = arr[random];
    arr[random] = temp;
  };

  Array.to_list(arr);
};

let make = _children => {
  ...component,
  initialState: () => {cards: generateDeck()},
  reducer: (action, state) =>
    switch (action) {
    | MoveCard => ReasonReact.Update({cards: []})
    | GenerateList => ReasonReact.Update({cards: generateDeck()})
    | Shuffle => ReasonReact.Update({cards: shuffleDeck(state.cards)})
    },
  render: self =>
    <>
      <div>
        <button onClick=(_ev => self.send(Shuffle))>
          (ReasonReact.string("shuffle"))
        </button>
      </div>
      <div>
        ...(
             self.state.cards
             |> List.map(a =>
                  <div>
                    <span
                      style=(
                        ReactDOMRe.Style.make(~marginRight="0.25rem", ())
                      )>
                      (ReasonReact.string(string_of_int(a.rank)))
                    </span>
                    <span>
                      (
                        (
                          switch (a.suit) {
                          | Hearts => "hearts"
                          | Diamonds => "diamonds"
                          | Clubs => "clubs"
                          | Spades => "spades"
                          }
                        )
                        |> ReasonReact.string
                      )
                    </span>
                  </div>
                )
             |> Array.of_list
           )
      </div>
    </>,
};