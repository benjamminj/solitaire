import * as range from 'lodash/fp/range';
import { Reducer, ActionCreator, ActionThunkCreator } from '../../types';
import { State, CardRefArray, Tableau, TableauRow } from './types';
import { get, cloneDeep } from 'lodash';
import { shuffleArray } from './utils';
import initialState from './initialState';
import { dealTableauCards } from './utils';

// Actions
export const DEALCARDS = 'DEALCARDS';
export const DEALCARDS_INVALID = 'DEALCARDS_INVALID';

const reducer: Reducer<State> = (state = initialState, action) => {
  switch (action.type) {
    case DEALCARDS: {
      const dealt = state.dealt;
      const deck = state.deck;

      const shuffledDeck = shuffleArray(Object.keys(deck));

      const tableauCards = shuffledDeck.slice(0, 28);
      const stockPile = shuffledDeck.slice(28);

      const tableau = dealTableauCards(tableauCards, cloneDeep(state.tableau));

      return {
        ...state,
        dealt: true,
        tableau,
        stock: stockPile,
      };
    }
    case DEALCARDS_INVALID:
    default:
      return state;
  }
};

// Actions
export const dealCards: ActionThunkCreator = () => (dispatch, getState) => {
  const dealt = getDealt(getState());
  return {
    type: dealt ? DEALCARDS_INVALID : DEALCARDS,
  };
};

// Selectors
export const getDealt = (state: State) => get(state, 'cards.dealt');
export const getDeck = (state: State) => get(state, 'cards.deck');
export const getTableau = (state: State) => get(state, 'cards.tableau');
export const getStock = (state: State) => get(state, 'cards.stock');

export type State = State;
export default reducer;
