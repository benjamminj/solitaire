import * as range from 'lodash/fp/range';
import { Reducer, ActionCreator, ActionThunkCreator } from '../../types';
import { State } from './types';
import { get } from 'lodash';
import { shuffleArray } from './utils';

import initialState from './initialState';

const SHUFFLEDECK = 'SHUFFLEDECK';

const reducer: Reducer<State> = (state = initialState, action) => {
  switch (action.type) {
    case SHUFFLEDECK:
      return {
        ...state,
        ...action.result,
      };
    default:
      return state;
  }
};

export const shuffleDeck: ActionThunkCreator = () => (dispatch, getState) => {
  const state = getState();
  const deck = get(state, 'cards.deck');

  const ids = Object.keys(deck);

  return {
    type: SHUFFLEDECK,
    result: {
      shuffledDeck: shuffleArray(ids),
    },
  };
};

export type State = State;
export default reducer;
