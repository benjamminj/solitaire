import * as range from 'lodash/fp/range';
import { Reducer, ActionCreator, ActionThunkCreator } from '../../types';
import { State } from './types';
import {get} from 'lodash';

import initialState from './initialState';

const SHUFFLEDECK = 'SHUFFLEDECK';

const reducer: Reducer<State> = (state = initialState, action) => {
  switch (action.type) {
    default:
      return state;
  }
};

export const shuffleDeck: ActionThunkCreator = () => (dispatch, getState) => {
  const state = getState();
  const deck = get(state, 'cards.deck');
  
  const ids = Object.keys(deck)

  return {
    type: SHUFFLEDECK,
    result: {}
  }
};

export type State = State;
export default reducer;
