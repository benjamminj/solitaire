let component = ReasonReact.statelessComponent("EmptyCard");

let buttonStyle =
  Css.(
    style([
      background(hex("dedede")),
      height(Global.Styles.cardHeight),
      width(pct(100.0)),
      borderWidth(`zero),
    ])
  );

let make = (~onClick, _children) => {
  ...component,
  render: _self => <button onClick className=buttonStyle />,
};