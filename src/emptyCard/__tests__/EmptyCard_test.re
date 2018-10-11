open Jest;
open Expect;
open ReactTestingLibrary;

describe("<EmptyCard />", () =>
  test("renders correctly", () =>
    <EmptyCard onClick={_ev => ()} />
    |> render
    |> container
    |> expect
    |> toMatchSnapshot
  )
);