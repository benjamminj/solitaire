import * as range from 'lodash/fp/range';
import { Card, CardRank, CardRankNumber, Deck, State, Suit } from './types';

export const getRank = (num: CardRankNumber): CardRank => {
  switch (num) {
    case '0':
      return 'K';
    case '1':
      return 'Q';
    case '2':
      return 'J';
    case '12':
      return 'A';
    default:
      return <CardRank>`${13 - +num}`;
  }
};

type GetInitialSuit = (x: Suit) => Deck;
export const getInitialSuit: GetInitialSuit = suitName => {
  return range(1, 14)
    .map((num: number) => {
      const value = <CardRankNumber>`${num % 13}`;
      const rank = getRank(value);

      return <Card>{
        id: `${suitName}-${rank}`,
        value: 13 - +value,
        rank,
        visible: false,
      };
    })
    .sort((first: Card, second: Card) => first.value - second.value)
    .reduce((obj: Deck, card: Card) => {
      obj[card.id] = card;
      return obj;
    }, {});
};

type GetInitialDeck = () => Deck;
const getInitialDeck: GetInitialDeck = () => {
  const suits = ['hearts', 'spades', 'diamonds', 'clubs'];
  return suits.reduce(
    (obj: Deck, suitName: Suit) => ({
      ...obj,
      ...getInitialSuit(suitName),
    }),
    {}
  );
};


export default <State>{
  deck: getInitialDeck(),
  shuffledDeck: [],
};
