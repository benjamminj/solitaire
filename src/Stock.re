let component = ReasonReact.statelessComponent("Stock");

let make = (~cards, ~onClick, _children) => {
  ...component,
  render: _self =>
    switch (cards) {
    | [] => <EmptyCard onClick=(_ev => onClick()) />
    | [card, ..._rest] =>
      <Card
        isSelected={false}
        card={...card, selectable: true}
        onClick=((~card as _c) => onClick())
      />
    },
};