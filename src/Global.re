module Styles = {
  open Css;

  let cardHeight = rem(4.75);
  let cardHeightMd = rem(7.25);

  let cardHeight_ = "4.75rem";

  type theme_ = {
    white: Css.color,
    black: Css.color,
    primary: Css.color,
    lightGrey: Css.color,
  };

  type xtheme_ = {
    white: string,
    black: string,
    primary: string,
  }

  let theme: theme_ = {
    white: hex("FFF"),
    black: hex("222"),
    primary: hex("1976D2"),
    lightGrey: hex("eee")
  };

  let xtheme: xtheme_ = {
    white: "#FFF",
    black: "#222",
    primary: "#1976D2",
  }
}