let component = ReasonReact.statelessComponent("Card");

let make = (~id: int, ~rank: int, ~suit: Types.suit, _children) => {
  ...component,
  render: _self =>
    <div key={string_of_int(id)}>
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
    </div>,
};