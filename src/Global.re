module Styles = {
  open Css;

  let cardHeight = rem(4.75);
  let cardHeightMd = rem(7.25);

  type theme_ = {
    text: Css.color,
    primary: Css.color,
    primaryLight: Css.color,
  };

  let theme = {
    text: hex("444"),
    primary: hex("2196f3"),
    primaryLight: hex("bbdefb")
  };
}