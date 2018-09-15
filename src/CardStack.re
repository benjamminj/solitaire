open Types;
let component = ReasonReact.statelessComponent("CardStack");

module Styles = {
  open Css;

  let stack = overrides => {
    let rules = List.append(overrides, [
      display(`flex),
      flexDirection(`column),
      padding(rem(0.25)),
    ]);

    style(rules);
  }
};

let make = (~cards, ~styles=[], ~onClickCard, _children) => {
  ...component,
  render: _self =>
    cards
    |> Array.mapi((i, cardList) =>
         <div
           key={"row-" ++ string_of_int(i)} className={Styles.stack(styles)}>
           {
             List.length(cardList) == 0 ?
               <button
                 onClick={_ev => onClickCard(i, ~card=None)}
                 style={
                   ReactDOMRe.Style.make(
                     ~background="none",
                     ~border="none",
                     (),
                   )
                 }>
                 {ReasonReact.string("EMPTY")}
               </button> :
               cardList
               |> List.rev_map(card =>
                    <Card
                      styles={Css.([borderColor(hex("f00"))])}
                      key={card.id |> string_of_int}
                      card
                      onClick={
                        (~card) =>
                          card.selectable ?
                            onClickCard(i, ~card=Some(card)) : ()
                      }
                    />
                  )
               |> Array.of_list
               |> ReasonReact.array
           }
         </div>
       )
    |> ReasonReact.array,
};