import { cloneDeep } from 'lodash/fp';
import {
  Card,
  Deck,
  Tableau,
  TableauRow,
  CardId,
  CardRefArray,
  Suit,
} from './types';

export const shuffleArray = (originalArray: any[]) => {
  // a little higher on memory, but small cost to pay for guaranteed immutability
  const arr = [...originalArray];
  let current = arr.length;
  let temp;
  let i;

  while (current) {
    i = Math.floor(Math.random() * current--);

    temp = arr[current];
    arr[current] = arr[i];
    arr[i] = temp;
  }

  return arr;
};

const getNonFilledRow = (tableau: Tableau): string | null => {
  const keys = Object.keys(tableau).sort((a, b) => +a - +b);
  const rowNumber = keys.find((key: TableauRow) => tableau[key].length < +key);
  return rowNumber ? `${rowNumber}` : null;
};

type DealTableauCards = (cards: CardRefArray, tableau: Tableau) => Tableau;
export const dealTableauCards: DealTableauCards = (cards, originalTableau) => {
  const { tableau: dealtTableau } = cards.reduce(
    (acc: { row: TableauRow; tableau: Tableau }, card, i) => {
      const { row, tableau } = acc;

      if (row) {
        tableau[row].push(card);
      }

      return {
        row:
          row === '7' || row === null
            ? getNonFilledRow(acc.tableau)
            : `${+row + 1}`,
        tableau: acc.tableau,
      };
    },
    {
      row: getNonFilledRow(originalTableau),
      tableau: originalTableau,
    },
  );

  return dealtTableau;
};

// Given a number of card IDs, and the deck, toggle the cards to be visible
type TurnCards = (ids: CardId[], deck: Deck, visible?: boolean) => Deck;
export const turnCards: TurnCards = (cardIds, originalDeck, visible = true) => {
  // Avoid mutating the nested object references inside of the decl
  const deck = cloneDeep(originalDeck);

  cardIds.forEach((id) => {
    // NOTE -- see if there's a better way to do this that is a little less side-effect heavy
    deck[id].visible = visible;
  });

  return deck;
};

export type validateCardBase = (card: Card, baseCard?: Card) => boolean;
export const validateCardBase: validateCardBase = (card, baseCard) => {
  if (baseCard) {
    const isRankDirectlyBelow = card.value === baseCard.value - 1;

    const suitIs = (str: Suit, suits: Suit[]): boolean =>
      suits.some(suit => str === suit);

    const isRedCard = (suit: Suit) => suitIs(suit, ['hearts', 'diamonds']);
    const isBlackCard = (suit: Suit) => suitIs(suit, ['clubs', 'spades']);

    const isOppositeSuit = isRedCard(card.suit)
      ? isBlackCard(baseCard.suit)
      : isRedCard(baseCard.suit);

    return isRankDirectlyBelow && isOppositeSuit;
  }

  if (card.rank === 'K') {
    return true;
  }

  return false;
};
