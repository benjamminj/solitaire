import * as range from 'lodash/fp/range';
import { Reducer, ActionCreator, ActionThunkCreator } from '../../types';
import { State, CardRefArray, Tableau, TableauRow } from './types';
import { get } from 'lodash';
import { shuffleArray } from './utils';

import initialState from './initialState';

const DEALCARDS = 'DEALCARDS';

const reducer: Reducer<State> = (state = initialState, action) => {
  switch (action.type) {
    case DEALCARDS:
      return {
        ...state,
        ...action.result,
      };
    default:
      return state;
  }
};

type DealTableauCards = (cards: CardRefArray, tableau: Tableau) => Tableau;
const dealTableauCards: DealTableauCards = (cards, originalTableau) => {
  const { tableau } = cards.reduce(
    (acc: { row: TableauRow; tableau: Tableau }, card, i) => {
      const { row, tableau } = acc;

      const getNonEmptyRow = (tableau: Tableau): string => {
        const keys = Object.keys(tableau).sort((a, b) => +a - +b);
        const rowNumber = keys.find((key: TableauRow) => tableau[key].length < +key);
        return `${rowNumber}`;
      };

      tableau[row].push(card);

      return {
        row: row === '7' ? getNonEmptyRow(acc.tableau) : `${+row + 1}`,
        tableau: acc.tableau,
      };
    },
    {
      row: '1',
      tableau: originalTableau,
    },
  );

  return tableau;
};

export const dealCards: ActionThunkCreator = () => (dispatch, getState) => {
  const state = getState();
  const deck = get(state, 'cards.deck');

  const shuffledDeck = shuffleArray(Object.keys(deck));
  const tableauCards = shuffledDeck.slice(0, 28);

  const stockPile = shuffledDeck.slice(28);

  const tableau = dealTableauCards(tableauCards, get(state, 'cards.tableau'));
  console.log(tableau);
  return {
    type: DEALCARDS,
    result: {
      stock: stockPile,
    },
  };
};

export type State = State;
export default reducer;
