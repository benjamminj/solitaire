import initialState from './initialState';
import { ActionCreator, Reducer } from '../../types';
import { State } from './types';
import { CardId, CardLocation } from '../cards/types';

// Actions
export const SAVE_CURRENTLOCATION = 'cards_SAVE_CURRENTLOCATION';

export const reducer: Reducer<State> = (state = initialState, action) => {
  switch (action.type) {
    case SAVE_CURRENTLOCATION:
      return {
        ...state,
        nextMove: {
          ...action.result
        }
      }
    default:
      return state;
  }
};

export const saveCurrentLocation: ActionCreator = (
  cards: CardId[],
  currentLocation: CardLocation,
) => ({
  type: SAVE_CURRENTLOCATION,
  result: {
    cards,
    currentLocation,
  }
});

export type State = State;
export default reducer;