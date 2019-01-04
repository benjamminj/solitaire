open Jest;
open JestDom
open ReactTestingLibrary;
open Types;

let mockCard = {
  id: 3,
  rank: 3,
  suit: Hearts,
  selectable: false,
  faceUp: false,
};

let onClickMock = (~card) => ();

describe("<Card />", () => {
    test("displays face up", () => {
      <Card card={...mockCard, faceUp: true} onClick=onClickMock isSelected=true />
      |> render
      |> getByText(~matcher=`Str("3"))
      |> expect
      |> toBeInTheDocument;
    })

  test("displays face down", () => {
    <Card card={mockCard} onClick={onClickMock} isSelected=true />
    |> render
    |> container
    |> Expect.expect
    |> Expect.toMatchSnapshot
  });
}
  );