open Types;
module Styles = Card_Styles;
module CardIcon = Card_Icon;

let css = Emotion.css;

let component = ReasonReact.statelessComponent("Card");

let getCardColor = suit =>
  switch (suit) {
  | Hearts => "red"
  | Diamonds => "red"
  | Clubs => "black"
  | Spades => "black"
  };

let getCardText = rank =>
  switch (rank) {
  | 1 => "A"
  | 13 => "K"
  | 12 => "Q"
  | 11 => "J"
  | num => num |> string_of_int
  };

let make = (~card, ~isSelected, ~onClick, ~styles="", _children) => {
  ...component,
  render: _self => {
    let {id, rank, suit, faceUp} = card;
    let idStr = string_of_int(id);

    let color = getCardColor(suit);
    let rankText = getCardText(rank);

    let onClick = _ev => onClick(~card);

    <button
      key=idStr
      id=idStr
      className={
        Emotion.cx([
          Styles.card(~textColor=color, ~faceUp, ~isSelected),
          styles,
        ])
      }
      onClick>
      {
        faceUp ?
          <div className=Styles.wrapper>
            <div className=Styles.header>
              <span className=Styles.upperRank>
                {ReasonReact.string(rankText)}
              </span>
              <Card_Icon className={Styles.headerIcon(color)} suit />
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