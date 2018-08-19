let component = ReasonReact.statelessComponent("App");

let make = (~name, _children) => {
  ...component,
  render: _self => <div> <Game /> </div>,
};