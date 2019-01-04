let component = ReasonReact.statelessComponent("Tableau");

let make = (~rows, ~selectedCardId, ~onClickCard, _children) => {
  ...component,
  render: _self =>
    rows
    |> Array.mapi((i, cardStack) =>
         <div key={"row-" ++ string_of_int(i)} className="">
           {
             switch (cardStack) {
             | [] => <EmptyCard onClick=(_ev => onClickCard(i, ~card=None)) />
             | [_a, ..._rest] =>
               <CardStack
                 cards=cardStack
                 selectedCardId
                 onClickCard=((~card) => onClickCard(i, ~card))
               />
             }
           }
         </div>
       )
    |> ReasonReact.array,
};