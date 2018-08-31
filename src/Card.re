open Types;
let component = ReasonReact.statelessComponent("Card");

let make = (~card, ~onClick, _children) => {
  ...component,
  render: _self => {
    let {id, rank, suit} = card;
    let idStr = string_of_int(id);
    let (text, color) =
      switch (suit) {
      | Hearts => ("hearts", "red")
      | Diamonds => ("diamonds", "red")
      | Clubs => ("clubs", "black")
      | Spades => ("spades", "black")
      };

    let rankText = 
      switch(rank) {
        | 1 => "A"
        | 13 => "K"
        | 12 => "Q"
        | 11 => "J"
        | num => num |> string_of_int
      };

    <button
      key=idStr
      id=idStr
      style={
        ReactDOMRe.Style.make(~background="none", ~border="none", ~color, ())
      }
      onClick={_ev => onClick(~card=Some(card))}>
      <span style={ReactDOMRe.Style.make(~marginRight="0.25rem", ())}>
        {ReasonReact.string(rankText)}
      </span>
      <span> {ReasonReact.string(text)} </span>
    </button>;
  },
};