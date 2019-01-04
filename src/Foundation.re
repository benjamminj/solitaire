open Types;
let component = ReasonReact.statelessComponent("Foundation");

module Styles = {
  let container = Emotion.css({|
    display: flex;
  |});
};

let make = (~rows, ~selectedCardId, ~onClickCard, _children) => {
  ...component,
  render: _self =>
    rows
    |> Array.mapi((i, row) => {
         let handleClick = (~card) =>
           onClickCard(~location=Foundation(i), ~card);

         switch (row) {
         | [] =>
           <EmptyCard
             key={"empty-" ++ string_of_int(i)}
             onClick=(_ev => handleClick(~card=None))
           />
         | [card, ..._rest] =>
           <Card
             isSelected={Utils.isCardSelected(selectedCardId, card.id)}
             key={string_of_int(card.id)}
             card
             onClick=((~card) => handleClick(~card=Some(card)))
           />
         };
       })
    |> ReasonReact.array,
  /* </div>, */
};