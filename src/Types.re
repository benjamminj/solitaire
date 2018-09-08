/*
 * Common data structures & types used throughout the application
 */
type suit =
  | Hearts
  | Diamonds
  | Clubs
  | Spades;

type card = {
  id: int,
  suit,
  rank: int,
  selectable: bool,
  faceUp: bool,
};

type cardList = list(card);
type cardArr = array(card);

type location = {
  foundation: array(cardList),
  tableau: array(cardList),
  stock: cardList,
  hand: cardList,
};

type locationKey =
  | Foundation(int)
  | Tableau(int)
  | Stock
  | Hand;

type move = {
  prev: option(locationKey),
  next: option(locationKey),
  card: option(card),
};

type moveKey =
  | Prev
  | Next;

type state = {
  location,
  move,
  moveKey,
};