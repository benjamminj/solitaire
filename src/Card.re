open Types;
let component = ReasonReact.statelessComponent("Card");

module Styles = {
  open Css;
  let gray = hex("333");

  let height_ = height(rem(6.75));
  let width_ = width(rem(4.0));
  let border_ = border(px(1), `solid, gray);

  let wrapper =
    style([display(`flex), flexDirection(`column), height(pct(100.0))]);

  let card = (~faceUp=false, ~textColor, ~styles) => {
    let rules =
      List.append(
        styles,
        [
          border_,
          padding(rem(0.5)),
          width_,
          height_,
          color(faceUp ? textColor : dodgerblue),
          backgroundColor(faceUp ? white : dodgerblue),
        ],
      );

    style(rules);
  };

  let iconWrapper =
    style([
      display(`flex),
      alignItems(`center),
      flexGrow(1),
      justifyContent(`center),
    ]);
  let icon = style([fontSize(rem(2.0))]);

  let upperRank = style([textAlign(`left)]);
  let lowerRank = style([textAlign(`right)]);
};

let make = (~card, ~onClick, ~styles=[], _children) => {
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
      className={Styles.card(~textColor=color, ~faceUp=card.faceUp, ~styles)}
      onClick>
      {
        card.faceUp ?
          <div className=Styles.wrapper>
            <span className=Styles.upperRank>
              {ReasonReact.string(rankText)}
            </span>
            <div className=Styles.iconWrapper>
              <span className=Styles.icon> {ReasonReact.string(text)} </span>
            </div>
            <span className=Styles.lowerRank>
              {ReasonReact.string(rankText)}
            </span>
          </div> :
          <div />
      }
    </button>;
  },
};