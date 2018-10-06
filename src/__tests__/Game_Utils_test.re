open Jest;
open Expect;
open Game_Utils;
open Belt;

describe("Game.Utils", () => {
  describe("generateSuit", () =>
    test("should create a suit with 13 cards", () => {
      let suit = generateSuit(99, Types.Hearts);
      expect(suit |> List.length) |> toEqual(13);
    })
  );

  describe("generateDeck", () =>
    test("should create a new deck of 52 cards", () => {
      let deck = generateDeck();
      expect(deck |> List.length) |> toEqual(52);
    })
  );

  describe("shuffleDeck", () =>
    test("should return a new deck that is not equal to the first deck", () => {
      let deck = generateDeck();
      let shuffled = shuffleDeck(123.0, deck);

      expect(deck) |> not_ |> toEqual(shuffled);
    })
  );

  describe("dealCards", () => {
    let (tableau, stock) = dealCards(generateDeck());

    test(
      "should deal number of cards to each teableau row that correspond to their index",
      () => {
        let (isEachRowCorrect, _i) =
          Array.reduce(
            tableau,
            (true, 0),
            ((isValid, i), row) => (
              /* Make sure that each & every row has only the number of cards as its' number */
              isValid && List.length(row) == i + 1,
              i + 1,
            ),
          );

        expect(isEachRowCorrect) |> toEqual(true);
      },
    );

    test("only the top card of each row should be visible", () => {
      open Types;

      let isEachRowValid =
        tableau
        ->Array.map(row =>
            switch (row) {
            | [] => false
            | [a, ...rest] =>
              a.faceUp && List.every(rest, card => card.faceUp == false)
            }
          )
        ->Array.every(row => row);

      expect(isEachRowValid) |> toEqual(true);
    });

    test("should put the remaining cards face down in the `stock`", () => {
      let isEveryCardFaceDown =
        List.every(stock, card => card.faceUp == false);
      let isStockCorrectLength = List.length(stock) == 24;

      let result = (isEveryCardFaceDown, isStockCorrectLength);
      expect(result) |> toEqual((true, true));
    });
  });
});