open Types;
let component = ReasonReact.statelessComponent("Foundation");

module Styles = {
  open Css;

  let container = style([display(`flex)]);
  let column = style([margin(rem(0.25))]);
};

let make = (~rows, ~onClickCard, _children) => {
  ...component,
  render: _self =>
    <div className=Styles.container>
      {
        rows
        |> Array.mapi((i, row) =>
             <div className=Styles.column>
               {
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
                     key={string_of_int(card.id)}
                     card
                     onClick=((~card) => handleClick(~card=Some(card)))
                   />
                 };
               }
             </div>
           )
        |> ReasonReact.array
      }
    </div>,
};