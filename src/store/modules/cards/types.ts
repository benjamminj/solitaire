export type CardRank =
  | 'A'
  | '2'
  | '3'
  | '4'
  | '5'
  | '6'
  | '7'
  | '8'
  | '9'
  | '10'
  | 'J'
  | 'Q'
  | 'K';

export type CardRankNumber =
  | '0'
  | '1'
  | '2'
  | '3'
  | '4'
  | '5'
  | '6'
  | '7'
  | '8'
  | '9'
  | '10'
  | '11'
  | '12';

export type Suit = 'hearts' | 'spades' | 'diamonds' | 'clubs';

export type Card = {
  id: string;
  suit: Suit;
  rank: CardRank;
  value: number;
  visible: boolean;
};

export type Deck = {
  [x: string]: Card;
};

export type State = {
  deck: Deck;
  shuffledDeck: string[];
};