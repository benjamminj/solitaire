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
  suit: suit,
  rank: int,
};

type cardList = list(card);