open Types;
let component = ReasonReact.statelessComponent("Card");

let make = (~id: int, ~rank: int, ~suit: Types.suit, ~onClick, _children) => {
  ...component,
  render: _self => {
    let idStr = string_of_int(id);

    <button
      key=idStr
      id=idStr
      style={ReactDOMRe.Style.make(~background="none", ~border="none", ())}
      onClick={_ev => onClick(~card={id, rank, suit})}>
      <span style={ReactDOMRe.Style.make(~marginRight="0.25rem", ())}>
        {rank |> string_of_int |> ReasonReact.string}
      </span>
      <span>
        {
          (
            switch (suit) {
            | Hearts => "hearts"
            | Diamonds => "diamonds"
            | Clubs => "clubs"
            | Spades => "spades"
            }
          )
          |> ReasonReact.string
        }
      </span>
    </button>;
  },
};