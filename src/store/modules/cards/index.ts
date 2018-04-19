import * as range from 'lodash/fp/range';
import { Reducer, ActionCreator, ActionThunkCreator } from '../../types';
import { State } from './types';

import initialState from './initialState';

const SHUFFLEDECK = 'SHUFFLEDECK';

const reducer: Reducer<State> = (state = initialState, action) => {
  switch (action.type) {
    default:
      return state;
  }
};

export const shuffleDeck: ActionThunkCreator = () => (dispatch, getState) => {
  console.log(getState());
  console.log('here');
  
  return {
    type: SHUFFLEDECK,
    result: {}
  }
};

export type State = State;
export default reducer;
