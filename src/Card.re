open Types;
let component = ReasonReact.statelessComponent("Card");

module CardIcon = {
  let component = ReasonReact.statelessComponent("CardIcon");
  let make = (~className, ~suit, _children) => {
    ...component,
    render: _self => {
      switch(suit) {
        | Hearts => <Icons.Hearts className />
        | Spades => <Icons.Spades className />
        | Clubs => <Icons.Clubs className />
        | Diamonds => <Icons.Diamonds className />
      }
    }
  }
}

module Styles = {
  open Css;
  open Global.Styles;

  let gray = hex("333");

  let width_ = width(pct(100.0));
  let border_ = border(px(1), `solid, gray);

  let wrapper =
    style([display(`flex), flexDirection(`column), height(pct(100.0))]);

  let header = style([display(`flex), justifyContent(`spaceBetween)]);

  let card = (~faceUp=false, ~textColor, ~styles) => {
    let rules =
      List.append(
        styles,
        [
          border_,
          padding(rem(0.5)),
          width_,
          height(cardHeight),
          `declaration(("color", faceUp ? textColor : "black")),
          backgroundColor(faceUp ? white : theme.primary),
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

  let icon = fill =>
    style([
      width(pct(100.0)),
      height(`auto),
      fontSize(rem(2.0)),
      maxWidth(pct(100.0)),
      `declaration(("fill", fill)),
    ]);

  let upperRank = style([textAlign(`left)]);
  let lowerRank = style([textAlign(`right)]);
};

let make = (~card, ~onClick, ~styles=[], _children) => {
  ...component,
  render: _self => {
    let {id, rank, suit} = card;
    let idStr = string_of_int(id);
    let (text, color) =
      switch (suit) {
      | Hearts => ({js|♥︎|js}, "red")
      | Diamonds => ({js|♦︎|js}, "red")
      | Clubs => ({js|♣︎|js}, "black")
      | Spades => ({js|♠︎|js}, "black")
      };

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
            <div className=Styles.header>
              <span className=Styles.upperRank>
                {ReasonReact.string(rankText)}
              </span>
              <span> {ReasonReact.string(text)} </span>
            </div>
            <div className=Styles.iconWrapper>
              <CardIcon className={Styles.icon(color)} suit />
            </div>
          </div> :
          <div />
      }
    </button>;
  },
};