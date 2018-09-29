open Types;

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