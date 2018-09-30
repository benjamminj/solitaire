let component = ReasonReact.statelessComponent("Heart");

let make = (~className="", ~height="16", ~width="16", _children) => {
  ...component,
  render: _self =>
    <svg viewBox="0 0 24 24" className height width>
      <path d="M19,12L12,22L5,12L12,2" />
    </svg>,
};