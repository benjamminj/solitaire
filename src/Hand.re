open Types;
let component = ReasonReact.statelessComponent("Hand");

module Styles = {
  let css = Emotion.css;

  let wrapper =
    css({|
    display: flex;
    justify-content: flex-end;
  |});

  let card = i => {
    let pct = i == 0 ? "0" : "-25%";

    css({j|
    margin-left: $pct;
    max-width: 50%;
  |j});
  };
};

let make = (~hand, ~selectedCardId, ~onClickCard, _children) => {
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
               isSelected={Utils.isCardSelected(selectedCardId, card.id)}
               styles={Styles.card(i)}
               onClick={
                 (~card) => onClickCard(~location=Hand, ~card=Some(card))
               }
             />
           )
        |> Array.of_list
        |> ReasonReact.array
      }
    </div>;
  },
};