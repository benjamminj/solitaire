module Styles = {
  open Css;

  let cardHeight = rem(4.75);
  let cardHeightMd = rem(7.25);

  let cardHeight_ = "4.75rem";

  type theme_ = {
    white: Css.color,
    black: Css.color,
    primary: Css.color,
  };

  let theme = {
    white: hex("FFF"),
    black: hex("222"),
    primary: hex("1976D2"),
  };
}