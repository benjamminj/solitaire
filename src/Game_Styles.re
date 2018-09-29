open Css;
open Global.Styles;

let container = style([maxWidth @@ rem(25.0), margin2(~v=`zero, ~h=`auto)]);

let grid =
  style([
    display(`grid),
    `declaration(("gridTemplateColumns", "repeat(7, 1fr)")),
    gridTemplateRows([cardHeight, auto]),
    gridRowGap(rem(1.0)),
    gridColumnGap(rem(0.25)),
  ]);

let newGame =
  style([
    borderWidth(`zero),
    backgroundColor(theme.primaryLight),
    color(theme.text),
    padding(rem(0.5)),
  ]);

let header = style([padding2(~v=rem(0.5), ~h=`zero)]);