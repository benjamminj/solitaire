module Styles = {
  open Css;

  let cardHeight = rem(4.75);
  let cardHeightMd = rem(7.25);

  type theme_ = {
    primary: Css.color,
  };

  let theme = {
    primary: hex("2196f3")
  };
}