open Global.Styles;
open Emotion;

let wrapper =
  css(
    {|
    display: flex;
    flex-direction: column;
    height: 100%;
  |},
  );

let header =
  css({|
    display: flex;
    justify-content: space-between;
  |});

let card = (~faceUp=false, ~textColor, ~isSelected) => {
  let color = faceUp ? textColor : "black";
  let bg = faceUp ? "white" : xtheme.primary;
  let black = xtheme.black;
  let boxShadow = isSelected ? "0 0 3px 1px rgba(0,0,0,0.5)" : "none";

  /* TODO -- fix the outline for focus state...need to figure out how to show something is selected */
  css(
    {j|
      border: 1px solid $black;
      padding: 0.25rem;
      width: 100%;
      height: $cardHeight_;
      color: $color;
      background-color: $bg;
      box-shadow: $boxShadow;

      &:focus {
        outline: none;
      }
    |j},
  );
};

let iconWrapper =
  css(
    {|
    display: flex;
    align-items: center;
    flex-grow: 1;
    justify-content: center;
  |},
  );

let icon = fill =>
  css({j|
    width: 100%;
    height: auto;
    fill: $fill;
  |j});

let headerIcon = fill =>
  css({j|
    max-width: 0.75rem;
    height: auto;
    fill: $fill;
  |j});

let upperRank = css({|
    text-align: left;
  |});