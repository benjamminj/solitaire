open Types;
let component = ReasonReact.statelessComponent("CardStack");

let make = (~cards, ~onClickCard, _children) => {
  ...component,
  render: _self =>
    cards
    |> Array.mapi((i, cardList) =>
         <div
           key={"row-" ++ string_of_int(i)}
           style={
             ReactDOMRe.Style.make(
               ~display="flex",
               ~flexDirection="column",
               ~padding="0.25rem",
               (),
             )
           }>
           {
             cardList
             |> List.rev_map(card =>
                  <Card
                    key={card.id |> string_of_int}
                    id={card.id}
                    rank={card.rank}
                    suit={card.suit}
                    onClick={i |> onClickCard}
                  />
                )
             |> Array.of_list
             |> ReasonReact.array
           }
         </div>
       )
    |> ReasonReact.array,
};