open Jest;
open Expect;

describe("EXAMPLE", () =>
  test("1 + 2 === 3", () =>
    expect(1 + 2) |> toBe(3)
  )
);