open Types;
let component = ReasonReact.statelessComponent("CardStack");

type direction =
  | Horizontal
  | Vertical;

module Styles = {
  open Css;

  let stack = overrides => {
    let rules =
      List.append(
        overrides,
        [display(`flex), flexDirection(`column), padding(rem(0.25))],
      );

    style(rules);
  };

  let card = (~i, ~direction) => {
    let getOverlap = (amt, i) => i == 0 ? px(0) : amt;
    let overlap =
      switch (direction) {
      | Horizontal => marginLeft(getOverlap(rem(-2.0), i))
      | Vertical => marginTop(getOverlap(rem(-5.0), i))
      };

    [zIndex(i), overlap];
  };
};

let make = (~cards, ~styles=[], ~direction=Vertical, ~onClickCard, _children) => {
  ...component,
  render: _self =>
    <div className={Styles.stack(styles)}>
      {
        cards
        |> List.rev
        |> List.mapi((j, card) =>
             <Card
               styles={Styles.card(~direction, ~i=j)}
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