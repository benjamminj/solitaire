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
  Test_Utils.genCardList(cards)->List.map(flipCardFaceDown);

describe("undoMove", () => {
  test("undoes a move from Hand --> Stock", () => {
    let location = {
      ...defaultLocation,
      stock:
        genNonSelectableList([(3, Hearts), (9, Spades), (1, Diamonds)])
    };

    let {stock, hand} =
      undoMove(
        {prev: Some(Hand), next: Some(Stock), card: None},
        location,
      );

    let expectedStock = [];
    let expectedHand =
      Test_Utils.genCardList([(1, Diamonds), (9, Spades), (3, Hearts)])
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
        Test_Utils.genCardList([
          (5, Diamonds),
          (13, Spades),
          (4, Hearts),
          (7, Clubs),
        ]),
    };

    let move = {prev: Some(Stock), next: Some(Hand), card: None};
    test("with nothing in stock", () => {
      let {stock, hand} = undoMove(move, location);

      let expectedHand = [
        {...Test_Utils.genCard(7, Clubs), selectable: true},
      ];

      let expectedStock =
        genNonSelectableList([(4, Hearts), (13, Spades), (5, Diamonds)])

      expect((stock, hand)) |> toEqual((expectedStock, expectedHand));
    });

    test("when items are in stock", () => {
      let location = {
        ...location,
        stock: genNonSelectableList([(3, Clubs), (9, Spades)]),
      };

      let {stock, hand} = undoMove(move, location);

      let expectedHand = [
        {...Test_Utils.genCard(7, Clubs), selectable: true},
      ];

      let expectedStock =
        List.concat(
          genNonSelectableList([
            (4, Hearts),
            (13, Spades),
            (5, Diamonds),
          ]),
          location.stock,
        )

      expect((stock, hand)) |> toEqual((expectedStock, expectedHand));
    });
  });
});