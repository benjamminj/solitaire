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

// TODO - make the typing on this more strict to basically just be a suit and a rank separated by a dash
export type CardId = string;

export type Card = {
  id: CardId;
  suit: Suit;
  rank: CardRank;
  value: number;
  visible: boolean;
};

export type Deck = {
  [x: string]: Card;
};

export type CardRefArray = CardId[];

export type TableauRow = '1' | '2' | '3' | '4' | '5' | '6' | '7';

export type TableauRowLocation =
  | 'tableau.1'
  | 'tableau.2'
  | 'tableau.3'
  | 'tableau.4'
  | 'tableau.5'
  | 'tableau.6'
  | 'tableau.7';

// Add type for foundation row
export type FoundationRowLocation =
  | 'foundation.hearts'
  | 'foundation.spades'
  | 'foundation.clubs'
  | 'foundation.diamonds';

export type Tableau = { [row in TableauRow]: CardRefArray };

export type Stock = CardRefArray;
export type Hand = CardRefArray;

export type Foundation = { [suit in Suit]: CardRefArray };
export type CardLocation = TableauRowLocation | 'hand' | FoundationRowLocation;

export type State = {
  deck: Deck;
  dealt: boolean;
  tableau: Tableau;
  stock: Stock;
  hand: Hand;
  foundation: Foundation;
};
