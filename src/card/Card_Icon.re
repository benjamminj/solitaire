open Types;

let component = ReasonReact.statelessComponent("CardIcon");

let make = (~className, ~suit, _children) => {
  ...component,
  render: _self =>
    switch (suit) {
    | Hearts => <Icons.Hearts className />
    | Spades => <Icons.Spades className />
    | Clubs => <Icons.Clubs className />
    | Diamonds => <Icons.Diamonds className />
    },
};