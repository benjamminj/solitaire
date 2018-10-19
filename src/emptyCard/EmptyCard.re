let component = ReasonReact.statelessComponent("EmptyCard");

let cardHeight = Global.Styles.cardHeight_;

let buttonStyle =
  Emotion.css(
    {j|
    background: rgba(0, 0, 0, 0.1);
    height: $cardHeight;
    width: 100%;
    border-width: 0;
  |j},
  );

let make = (~onClick, _children) => {
  ...component,
  render: _self => <button onClick className=buttonStyle />,
};