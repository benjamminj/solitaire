open Types;
open Belt;
open Jest;
open Expect;
open Undo;

let defaultLocation = {
  foundation: [|[], [], [], []|],
  stock: [],
  hand: [],
  tableau: [|[], [], [], [], [], [], []|],
};

let flipCardFaceDown = c => {...c, selectable: false, faceUp: false};
let genNonSelectableList = cards =>
  TestUtils.genCardList(cards)->List.map(flipCardFaceDown);

describe("undoMove", () => {
  test("undoes a move from Hand --> Stock", () => {
    let location = {
      ...defaultLocation,
      stock:
        genNonSelectableList([(3, Hearts), (9, Spades), (1, Diamonds)]),
    };

    let {stock, hand} =
      undoMove(
        {prev: Hand, next: Stock, card: None, didFlip: false},
        location,
      );

    let expectedStock = [];
    let expectedHand =
      TestUtils.genCardList([(1, Diamonds), (9, Spades), (3, Hearts)])
      ->List.mapWithIndex((i, card) =>
          {...card, selectable: i == 0, faceUp: true}
        );

    expect((stock, hand)) |> toEqual((expectedStock, expectedHand));
  });

  describe("undoes a move from Stock --> Hand", () => {
    let location = {
      ...defaultLocation,
      stock: [],
      hand:
        TestUtils.genCardList([
          (5, Diamonds),
          (13, Spades),
          (4, Hearts),
          (7, Clubs),
        ]),
    };

    let move: moveEntry = {
      prev: Stock,
      next: Hand,
      card: None,
      didFlip: false,
    };
    test("with nothing in stock", () => {
      let {stock, hand} = undoMove(move, location);

      let expectedHand = [
        {...TestUtils.genCard(7, Clubs), selectable: true},
      ];

      let expectedStock =
        genNonSelectableList([(4, Hearts), (13, Spades), (5, Diamonds)]);

      expect((stock, hand)) |> toEqual((expectedStock, expectedHand));
    });

    test("when items are in stock", () => {
      let location = {
        ...location,
        stock: genNonSelectableList([(3, Clubs), (9, Spades)]),
      };

      let {stock, hand} = undoMove(move, location);

      let expectedHand = [
        {...TestUtils.genCard(7, Clubs), selectable: true},
      ];

      let expectedStock =
        List.concat(
          genNonSelectableList([(4, Hearts), (13, Spades), (5, Diamonds)]),
          location.stock,
        );

      expect((stock, hand)) |> toEqual((expectedStock, expectedHand));
    });
  });

  describe("undoes a move from Tableau --> Foundation", () => {
    let location = {
      ...defaultLocation,
      foundation: [|
        [],
        [],
        TestUtils.genCardList([(2, Hearts), (1, Hearts)]),
        [],
      |],
    };

    let move: moveEntry = {
      prev: Tableau(3),
      next: Foundation(2),
      card: Some(TestUtils.genCard(2, Hearts)),
      didFlip: false,
    };

    test(
      "removes the card from the `foundation` and adds it to the tableau", () => {
      let result = undoMove(move, location);
      let rowFoundationExpected = [TestUtils.genCard(1, Hearts)];
      let rowTableauExpected = [TestUtils.genCard(2, Hearts)];
      let rowFoundationResult = result.foundation->Array.getUnsafe(2);
      let rowTableauResult = result.tableau->Array.getUnsafe(3);

      expect((rowFoundationResult, rowTableauResult))
      |> toEqual((rowFoundationExpected, rowTableauExpected));
    });

    test("handles flipping of tableau card if it needs to be flipped", () => {
      let tableau = {
        let copy = Array.copy(location.tableau);
        copy[3] = TestUtils.genCardList([(4, Spades), (9, Hearts)]);
        copy;
      };

      let location = {...location, tableau};

      let result = undoMove({...move, didFlip: true}, location);

      let rowFoundationExpected = [TestUtils.genCard(1, Hearts)];
      let rowTableauExpected = [
        TestUtils.genCard(2, Hearts),
        ...genNonSelectableList([(4, Spades), (9, Hearts)]),
      ];
      /* let tableauRowExpected = Some([]) */
      let rowTableauResult = result.tableau->Array.getUnsafe(3);
      let rowFoundationResult = result.tableau->Array.getUnsafe(2);
      expect(())
    });
  });
});