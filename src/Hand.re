open Types;
let component = ReasonReact.statelessComponent("Hand");

let make = (~hand, ~onClickCard, _children) => {
  ...component,
  render: _self => {
    let displayedCards =
      switch (hand) {
      | [] => []
      | [a] => [a]
      | [a, b] => [a, b]
      | [a, b, c, ..._rest] => [a, b, c]
      };

    /* 
      TODO -- may need to create an internal grid with the layers here... 
      It would be 50 / 50 inheriting the grid-gap of its parent.
      this could mean it's more worth it to split the CardStack component just 
      up into the Hand & the Foundation Stacks 
    */
    <CardStack
      styles=Css.[flexDirection(`row)]
      cards=displayedCards
      direction=Horizontal
      onClickCard={(~card) => onClickCard(~location=Hand, ~card)}
    />;
  },
};