open Types;

let generateSuit = (idPrefix, suit: suit): list(card) => {
  let ranks = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13];

  ranks
  ->Belt.List.map(rank =>
      {
        id: idPrefix * 100 + rank,
        suit,
        rank,
        selectable: false,
        faceUp: false,
      }
    );
};

let generateDeck = (): list(card) => {
  let suits = [Hearts, Diamonds, Clubs, Spades];

  suits->Belt.List.mapWithIndex(generateSuit)->Belt.List.flatten;
};

let shuffleDeck = (randomNumber, deck: list(card)): list(card) => {
  let arr = deck->Belt.List.toArray->Belt.Array.copy;

  let start = Belt.Array.length(arr) - 1;

  for (i in start downto 1) {
    let temp = arr[i];

    let random =
      randomNumber *. float_of_int(i - 1) |> floor |> int_of_float;

    arr[i] = arr[random];
    arr[random] = temp;
  };

  Belt.List.fromArray(arr);
};

let dealCards = cards => {
  let (cardsToDeal, stock) =
    cards
    |> Belt.List.toArray
    |> Belt.Array.(
         arr => (
           slice(arr, ~offset=0, ~len=28),
           slice(arr, ~offset=28, ~len=arr->length - 28)
           |> Belt.List.fromArray,
         )
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

        Belt.Array.makeBy(
          7,
          i => {
            let amt = i + 1;
            let nextStart = start^ + amt;
            let items = Belt.Array.slice(arr, ~offset=start^, ~len=amt);
            items[0] = {...items[0], faceUp: true, selectable: true};

            start := nextStart;
            items |> Belt.List.fromArray;
          },
        );
      }
    );

  (tableau, stock);
};