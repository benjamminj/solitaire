open Types;
let css = Emotion.css;

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
  open Global.Styles;
  
  let wrapper = css({| 
    display: flex;
    flex-direction: column;
    height: 100%;
  |});

  let header = css({| 
    display: flex;
    justify-content: space-between;
  |});

  let card = (~faceUp=false, ~textColor) => {
    let color = faceUp ? textColor : "black";
    let bg = faceUp ? "white" : xtheme.primary;
    let black = xtheme.black;

    css({j|
      border: 1px solid $black;
      padding: 0.25rem;
      width: 100%;
      height: $cardHeight_;
      color: $color;
      background-color: $bg;
    |j});
  };

  let iconWrapper = css({| 
    display: flex;
    align-items: center;
    flex-grow: 1;
    justify-content: center;
  |});

  let icon = fill => css({j| 
    width: 100%;
    height: auto;
    fill: $fill;
  |j});

  let headerIcon = fill => css({j| 
    max-width: 0.75rem;
    height: auto;
    fill: $fill;
  |j});

  let upperRank = css({| 
    text-align: left;
  |});
};

let make = (~card, ~onClick, ~styles="", _children) => {
  ...component,
  render: _self => {
    let {id, rank, suit} = card;
    let idStr = string_of_int(id);
    let color =
      switch (suit) {
      | Hearts => "red"
      | Diamonds => "red"
      | Clubs => "black"
      | Spades => "black"
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
      className={Emotion.cx([
        Styles.card(~textColor=color, ~faceUp=card.faceUp),
        styles,
      ])}
      onClick>
      {
        card.faceUp ?
          <div className=Styles.wrapper>
            <div className=Styles.header>
              <span className=Styles.upperRank>
                {ReasonReact.string(rankText)}
              </span>
              <CardIcon className={Styles.headerIcon(color)} suit />
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