import * as range from 'lodash/fp/range';
import { Reducer } from '../../types';
import { State } from './types'

import initialState from './initialState';

const reducer: Reducer<State> = (state = initialState, action) => {
  switch (action.type) {
    default:
      return state;
  }
};

export default reducer;
