open Types;
let component = ReasonReact.statelessComponent("Hand");

module Styles = {
  open Css;

  let wrapper = style([
    display(`flex),
    justifyContent(`flexEnd),
  ]);

  let card = i => {
    let overlap = i == 0 ? `zero : rem(-2.0);

    [marginLeft(overlap), maxWidth(pct(50.0))];
  };
};

let make = (~hand, ~onClickCard, _children) => {
  ...component,
  render: _self => {
    let displayedCards =
      switch (hand) {
      | [] => []
      | [a] => [a]
      | [a, b] => [b, a]
      | [a, b, c, ..._rest] => [c, b, a]
      };

    /*
       TODO -- may need to create an internal grid with the layers here...
       It would be 50 / 50 inheriting the grid-gap of its parent.
       this could mean it's more worth it to split the CardStack component just
       up into the Hand & the Foundation Stacks
     */
    <div className=Styles.wrapper>
      {
        displayedCards
        |> List.mapi((i, card) =>
             <Card
               key={card.id |> string_of_int}
               card
               styles={Styles.card(i)}
               onClick={(~card) => onClickCard(~location=Hand, ~card=Some(card))}
             />
           )
        |> Array.of_list
        |> ReasonReact.array
      }
    </div>;
  },
};