import * as range from 'lodash/fp/range';
import { Card, CardRank, CardRankNumber, Deck, State, Suit } from './types';

type GetRankFromRemainder = (x: CardRankNumber) => CardRank;
export const getRankFromRemainder: GetRankFromRemainder = num => {
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
      return `${13 - +num}` as CardRank;
  }
};

type GetInitialSuit = (x: Suit) => Deck;
export const getInitialSuit: GetInitialSuit = suitName => {
  return range(1, 14)
    .map((num: number) => {
      const value = `${num % 13}` as CardRankNumber;
      const rank = getRankFromRemainder(value);

      return {
        id: `${suitName}-${rank}`,
        rank,
        suit: suitName,
        value: 13 - +value,
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
export const getInitialDeck: GetInitialDeck = () => {
  const suits = ['hearts', 'spades', 'diamonds', 'clubs'];
  return suits.reduce(
    (obj: Deck, suitName: Suit) => ({
      ...obj,
      ...getInitialSuit(suitName),
    }),
    {}
  );
};

export default {
  deck: getInitialDeck(),
  shuffledDeck: [],
} as State;
