module Styles = {
  open Css;

  let cardHeight = rem(4.75);
  let cardHeightMd = rem(7.25);

  type theme_ = {
    white: Css.color,
    black: Css.color,
    primary: Css.color,
    lightGrey: Css.color,
  };

  let theme = {
    white: hex("FFF"),
    black: hex("222"),
    primary: hex("1976D2"),
    lightGrey: hex("eee")
  };
}