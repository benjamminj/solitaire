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

const getNonEmptyRow = (tableau: Tableau): string | null => {
  const keys = Object.keys(tableau).sort((a, b) => +a - +b);
  const rowNumber = keys.find((key: TableauRow) => tableau[key].length < +key);
  return rowNumber ? `${rowNumber}` : null;
};

type DealTableauCards = (cards: CardRefArray, tableau: Tableau) => Tableau;
const dealTableauCards: DealTableauCards = (cards, originalTableau) => {
  const { tableau: dealtTableau } = cards.reduce(
    (acc: { row: TableauRow; tableau: Tableau }, card, i) => {
      const { row, tableau } = acc;

      if (row) {
        tableau[row].push(card);
      }

      return {
        row:
          row === '7' || row === null
            ? getNonEmptyRow(acc.tableau)
            : `${+row + 1}`,
        tableau: acc.tableau,
      };
    },
    {
      row: getNonEmptyRow(originalTableau),
      tableau: originalTableau,
    },
  );

  return dealtTableau;
};

export const dealCards: ActionThunkCreator = () => (dispatch, getState) => {
  const state = getState();
  const dealt = getDealt(state);

  const deck = getDeck(state);

  const shuffledDeck = shuffleArray(Object.keys(deck));

  const tableauCards = shuffledDeck.slice(0, 28);
  const stockPile = shuffledDeck.slice(28);

  const tableau = dealTableauCards(tableauCards, getTableau(state));
  console.log(tableau);
  return {
    type: DEALCARDS,
    result: {
      dealt: true,
      ...(dealt
        ? {}
        : {
          tableau,
          stock: stockPile,
        }),
    },
  };
};

// Selectors
const getDealt = (state: State) => get(state, 'cards.dealt');
const getDeck = (state: State) => get(state, 'cards.deck');
const getTableau = (state: State) => get(state, 'cards.tableau');
const getStock = (state: State) => get(state, 'cards.stock');

export type State = State;
export default reducer;
