open Jest;
open Expect;

let genCard = (rank, suit) =>
  Types.{id: rank, suit, rank, selectable: true, faceUp: true};

describe("Moves", () => {
  describe("isOppositeSuit", () => {
    let isOppositeSuit = Moves.isOppositeSuit;

    let genCard = genCard(1);
    let genCards = (suitA, suitB) => (genCard(suitA), genCard(suitB));

    test("should return `true` if Hearts --> Spades", () => {
      let (first, second) = genCards(Hearts, Spades);

      let result = isOppositeSuit(first, second);
      expect(result) |> toEqual(true);
    });

    test("should return `true` if Hearts --> Clubs", () => {
      let (first, second) = genCards(Hearts, Clubs);

      let result = isOppositeSuit(first, second);
      expect(result) |> toEqual(true);
    });

    test("should return `true` if Diamonds --> Clubs", () => {
      let (first, second) = genCards(Diamonds, Clubs);

      let result = isOppositeSuit(first, second);
      expect(result) |> toEqual(true);
    });

    test("should return `true` if Diamonds --> Spades", () => {
      let (first, second) = genCards(Diamonds, Spades);

      let result = isOppositeSuit(first, second);
      expect(result) |> toEqual(true);
    });

    test("should return `true` if Clubs --> Hearts", () => {
      let (first, second) = genCards(Clubs, Hearts);

      let result = isOppositeSuit(first, second);
      expect(result) |> toEqual(true);
    });

    test("should return `true` if Clubs --> Diamonds", () => {
      let (first, second) = genCards(Clubs, Diamonds);

      let result = isOppositeSuit(first, second);
      expect(result) |> toEqual(true);
    });

    test("should return `true` if Spades --> Hearts", () => {
      let (first, second) = genCards(Spades, Hearts);

      let result = isOppositeSuit(first, second);
      expect(result) |> toEqual(true);
    });

    test("should return `true` if Spades --> Diamonds", () => {
      let (first, second) = genCards(Spades, Diamonds);

      let result = isOppositeSuit(first, second);
      expect(result) |> toEqual(true);
    });

    test("should return `false` if Hearts --> Hearts", () => {
      let (first, second) = genCards(Hearts, Hearts);

      let result = isOppositeSuit(first, second);
      expect(result) |> toEqual(false);
    });

    test("should return `false` if Hearts --> Diamonds", () => {
      let (first, second) = genCards(Hearts, Diamonds);

      let result = isOppositeSuit(first, second);
      expect(result) |> toEqual(false);
    });

    test("should return `false` if Diamonds --> Diamonds", () => {
      let (first, second) = genCards(Diamonds, Diamonds);

      let result = isOppositeSuit(first, second);
      expect(result) |> toEqual(false);
    });

    test("should return `false` if Diamonds --> Hearts", () => {
      let (first, second) = genCards(Diamonds, Hearts);

      let result = isOppositeSuit(first, second);
      expect(result) |> toEqual(false);
    });

    test("should return `false` if Clubs --> Clubs", () => {
      let (first, second) = genCards(Clubs, Clubs);

      let result = isOppositeSuit(first, second);
      expect(result) |> toEqual(false);
    });

    test("should return `false` if Clubs --> Spades", () => {
      let (first, second) = genCards(Clubs, Spades);

      let result = isOppositeSuit(first, second);
      expect(result) |> toEqual(false);
    });

    test("should return `false` if Spades --> Spades", () => {
      let (first, second) = genCards(Spades, Spades);

      let result = isOppositeSuit(first, second);
      expect(result) |> toEqual(false);
    });

    test("should return `false` if Spades --> Clubs", () => {
      let (first, second) = genCards(Spades, Clubs);

      let result = isOppositeSuit(first, second);
      expect(result) |> toEqual(false);
    });
  });

  describe("validateMoveToTableau", () => {
    let validateMoveToTableau = Moves.validateMoveToTableau;
    let genCard = (rank, suit) =>
      Types.{id: rank, suit, rank, selectable: true, faceUp: true};
    let list =
      Types.[genCard(12, Hearts), genCard(5, Spades), genCard(7, Clubs)];

    test(
      "should return `true` if opposite color suit & ranked 1 below first card in tableau",
      () => {
        let result =
          validateMoveToTableau(
            ~card=genCard(11, Spades),
            ~destination=list,
          );
        expect(result) |> toEqual(true);
      },
    );

    test("should return `false` if isn't opposite color suit", () => {
      let result =
        validateMoveToTableau(~card=genCard(11, Hearts), ~destination=list);
      expect(result) |> toEqual(false);
    });

    test("should return `false` if isn't ranked 1 below 1st card", () => {
      let result =
        validateMoveToTableau(~card=genCard(7, Spades), ~destination=list);
      expect(result) |> toEqual(false);
    });

    test(
      "should return `true` if destination row is empty & card is a King", () => {
      let result =
        validateMoveToTableau(~card=genCard(13, Spades), ~destination=[]);
      expect(result) |> toEqual(true);
    });

    test(
      "should return `false` if destination row is empty & card is not a King",
      () => {
      let result =
        validateMoveToTableau(~card=genCard(4, Spades), ~destination=[]);
      expect(result) |> toEqual(false);
    });
  });

  describe("validateMoveToFoundation", () => {
    let validateMoveToFoundation = Moves.validateMoveToFoundation;
    let list = [
      genCard(3, Hearts),
      genCard(2, Hearts),
      genCard(1, Hearts),
    ];

    test(
      "should return `true` if card is same suit & ranked 1 higher than first card in destination",
      () => {
        let result =
          validateMoveToFoundation(
            ~card=genCard(4, Hearts),
            ~destination=list,
          );
        expect(result) |> toEqual(true);
      },
    );

    test("should return `false` if card is different suit than destination", () => {
      let result = validateMoveToFoundation(~card=genCard(4, Spades), ~destination=list);
      expect(result) |> toEqual(false);
    });

    test("should return `false` if card isn't ranked 1 higher than destination", () => {
      let result = validateMoveToFoundation(~card=genCard(5, Hearts), ~destination=list);
      expect(result) |> toEqual(false);
    });

    test("should return `true` if card is an Ace & destination is empty", () => {
      let result = validateMoveToFoundation(~card=genCard(1, Hearts), ~destination=[]);
      expect(result) |> toEqual(true);
    });

    test("should return `false` if card isn't an Ace & destination is empty", () => {
      let result = validateMoveToFoundation(~card=genCard(3, Hearts), ~destination=[]);
      expect(result) |> toEqual(false);
    });
  });

  describe("filterOutCard", () => {
    let filterOutCard = Moves.filterOutCard;
    test("should remove the matching card from the list", () => {
      let card = genCard(1, Hearts);
      let list = [card, genCard(4, Spades), genCard(13, Diamonds)];
      let result = filterOutCard(card, list);
      let [first, ...expected] = list;
      expect(result) |> toEqual(expected);
    })
  })

  describe("getListPlusCard", () => {
    let getListPlusCard = Moves.getListPlusCard;
    let list1 = [genCard(1, Spades)];
    let list2 = [genCard(4, Hearts), genCard(9, Diamonds)];
    let arr = [|list1, list2|];

    test("should add the card to the list", () => {
      let card = genCard(3, Spades);
      let result = getListPlusCard(card, 1, arr);
      
      expect(result[1]) |> toEqual([card, ...list2]);
    });

    test("shouldn't modify the original array", () => {
      let card = genCard(3, Spades);
      let _result = getListPlusCard(card, 1, arr);

      expect(list2) |> toEqual(list2);
    })
  });

  describe("makeFirstCardSelectable", () => {
    let makeFirstCardSelectable = Moves.makeFirstCardSelectable;
    
    test("should flip the `selectable` key on the first card of the list", () => {
      let card = { ...genCard(1, Hearts), selectable: false };

      let list = [card, genCard(2, Spades), genCard(12, Diamonds)];

      let result = makeFirstCardSelectable(list) |> List.hd;
      expect(result) |> toEqual({ ...card, selectable: true })
    });
  })
});