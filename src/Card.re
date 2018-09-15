open Types;
let component = ReasonReact.statelessComponent("Card");

module Styles = {
  open Css;
  let gray = hex("a3a3a3");
  
  let height_ = height(rem(7.25));
  let width_ = width(rem(4.0));
  let border_ = border(px(1), `solid, gray);
  
  let wrapper = style([
    display(`flex),
    flexDirection(`column)
  ]);

  let card = (~faceUp=false, ~textColor) =>
    style([
      border_,
      padding(rem(0.5)),
      width_,
      height_,
      color(faceUp ? textColor : dodgerblue),
    ]);

  let icon = style([fontSize(rem(2.0))]);

  let upperRank = style([textAlign(`left)]);
  let lowerRank = style([textAlign(`right)]);

  let hiddenCard = style([
    border_,
    width_,
    height_,
  ]);
};

let make = (~card, ~onClick, _children) => {
  ...component,
  render: _self => {
    let {id, rank, suit} = card;
    let idStr = string_of_int(id);
    let (text, color) =
      Css.(
        switch (suit) {
        | Hearts => ({js|♥︎|js}, red)
        | Diamonds => ({js|♦︎|js}, red)
        | Clubs => ({js|♣︎|js}, black)
        | Spades => ({js|♠︎|js}, black)
        }
      );

    let rankText =
      switch (rank) {
      | 1 => "A"
      | 13 => "K"
      | 12 => "Q"
      | 11 => "J"
      | num => num |> string_of_int
      };

    let onClick = _ev => onClick(~card);

    <button
      key=idStr
      id=idStr
      className={Styles.card(~textColor=color, ~faceUp=card.faceUp)}
      onClick>
      {
        card.faceUp ?
          <div className=Styles.wrapper>
            <span className=Styles.upperRank> {ReasonReact.string(rankText)} </span>
            <span className=Styles.icon> {ReasonReact.string(text)} </span>
            <span className=Styles.lowerRank>
              {ReasonReact.string(rankText)}
            </span>
          </div> :
          <span> {ReasonReact.string("HIDDEN")} </span>
      }
    </button>;
  },
};