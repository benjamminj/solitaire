open Types;
let component = ReasonReact.statelessComponent("Card");

module Styles = {
  open Css;
  let gray = hex("a3a3a3");

  let card = style([
    border(px(1), `solid, gray),
    padding(rem(0.5)),
  ])
}

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
      switch (rank) {
      | 1 => "A"
      | 13 => "K"
      | 12 => "Q"
      | 11 => "J"
      | num => num |> string_of_int
      };

    let onClick =
      card.selectable ? _ev => onClick(~card=Some(card)) : (_ev => ());

    <button
      key=idStr
      id=idStr
      className={Styles.card}
      onClick>
      {
        card.faceUp ?
          <span style={ReactDOMRe.Style.make(~color, ())}>
            <span style={ReactDOMRe.Style.make(~marginRight="0.25rem", ())}>
              {ReasonReact.string(rankText)}
            </span>
            <span> {ReasonReact.string(text)} </span>
          </span> :
          <span> {ReasonReact.string("HIDDEN")} </span>
      }
    </button>;
  },
};