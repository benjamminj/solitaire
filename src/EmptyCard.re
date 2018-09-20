let component = ReasonReact.statelessComponent("EmptyCard");

let buttonStyle =
  Css.(
    style([
      background(hex("dedede")),
      height(rem(6.75)),
      width(rem(4.0)),
      borderWidth(`zero),
    ])
  );

let make = (~onClick, _children) => {
  ...component,
  render: _self => <button onClick className=buttonStyle />,
};