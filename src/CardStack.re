open Types;
let isCardSelected = Utils.isCardSelected;

let component = ReasonReact.statelessComponent("CardStack");

type direction =
  | Horizontal
  | Vertical;

module Styles = {
  let css = Emotion.css;

  let stack = css({|
    display: flex;
    flex-direction: column;
  |});

  let card = (~i, ~direction) => {
    let getOverlap = (amt, i) => i == 0 ? "0" : amt;
    let overlap =
      switch (direction) {
      | Horizontal => "margin-left: " ++ getOverlap("-2rem", i)
      | Vertical => "margin-top: " ++ getOverlap("-3.5rem", i)
      };

    css({j|
      z-index: $i;
      $overlap;
    |j});
  };
};

let make = (~cards, ~styles="", ~selectedCardId, ~direction=Vertical, ~onClickCard, _children) => {
  ...component,
  render: _self =>
    <div className={Emotion.cx([Styles.stack, styles])}>
      {
        cards
        |> List.rev
        |> List.mapi((i, card) =>
             <Card
               isSelected={isCardSelected(selectedCardId, card.id)}
               styles={Styles.card(~direction, ~i)}
               key={card.id |> string_of_int}
               card
               onClick={
                 (~card) =>
                   card.selectable ? onClickCard(~card=Some(card)) : ()
               }
             />
           )
        |> Array.of_list
        |> ReasonReact.array
      }
    </div>,
};