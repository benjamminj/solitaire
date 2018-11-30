open Types;

let genCard = (rank, suit) => {
  id: rank,
  suit,
  rank,
  selectable: true,
  faceUp: true,
};

let genCardList = List.map(((rank, suit)) => genCard(rank, suit));