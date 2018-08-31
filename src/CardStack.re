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
             List.length(cardList) == 0 ?
               <button
                 onClick={_ev => onClickCard(i, ~card=None)}
                 style={
                   ReactDOMRe.Style.make(
                     ~background="none",
                     ~border="none",
                     (),
                   )
                 }>
                 {ReasonReact.string("EMPTY")}
               </button> :
               cardList
               |> List.rev_map(card =>
                    <Card
                      key={card.id |> string_of_int}
                      card
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