open Global.Styles;

let css = Emotion.css;

let container = css({| 
  max-width: 25rem;
  margin: 0 auto;
|});

let grid = css({j| 
  display: grid;
  grid-template-columns: repeat(7, 1fr);
  grid-template-rows: $cardHeight_;
  grid-row-gap: 1rem;
  grid-column-gap: 0.25rem;
|j});

let {primary, white} = xtheme;

let newGame = css({j| 
  border-width: 0;
  background-color: $primary;
  color: $white;
  padding: 0.5rem;
|j})

let header = css({| 
  padding: 0.5rem 0;
|})