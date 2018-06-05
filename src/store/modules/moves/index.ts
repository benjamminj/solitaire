import initialState from './initialState';
import { ActionCreator, Reducer, ActionThunkCreator } from '../../types';
import { State, Move } from './types';
import {
  CardId,
  CardLocation,
  Deck,
  Foundation,
  FoundationRowLocation,
} from '../cards/types';
import { get, first, set, cloneDeep } from 'lodash';
import { validateCardBase, validateFoundationMove } from '../cards/utils';
import { getDeck, getFoundation } from '../cards';

// Actions
export const SAVE_CURRENTLOCATION = 'cards_SAVE_CURRENTLOCATION';
export const APPLY_NEXT_LOCATION = 'cards_APPLY_NEXT_LOCATION';
export const APPLY_NEXT_LOCATION_INVALID = 'cards_APPLY_NEXT_LOCATION_INVALID';

export const reducer: Reducer<State> = (state = initialState, action) => {
  switch (action.type) {
    case SAVE_CURRENTLOCATION:
      return {
        ...state,
        nextMove: {
          ...action.result,
        },
      };
    case APPLY_NEXT_LOCATION: {
      const destination = action.result.nextLocation as CardLocation;
      const move = { ...state.nextMove, destination } as Move;
      // dont need to put the next location here, can just push it into the history

      return {
        ...state,
        nextMove: {},
        history: [...state.history, move],
      };
    }
    case APPLY_NEXT_LOCATION_INVALID:
      return {
        ...state,
        nextMove: {},
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
  },
});

export const applyNextLocation: ActionThunkCreator = (nextLocation: CardLocation) => (dispatch, getState) => {
  const state = getState();
  const nextMove: Move = getNextMove(state);
  console.log(nextMove);

  const isValidMove = validateMove({
    cards: nextMove.cards,
    currentLocation: nextMove.currentLocation,
    nextLocation,
    deck: getDeck(state),
    foundation: getFoundation(state),
  });

  return isValidMove
    ? {
      type: APPLY_NEXT_LOCATION,
      result: {
        nextLocation,
      },
    }
    : { type: APPLY_NEXT_LOCATION_INVALID };
};

type ValidateMove = (
  args: {
  cards: CardId[];
  currentLocation: CardLocation;
  nextLocation: CardLocation;
  deck: Deck;
  foundation: Foundation;
  }
) => boolean;
export const validateMove: ValidateMove = ({
  cards,
  currentLocation,
  nextLocation,
  deck,
  foundation,
}) => {
  const isValidTableauMove =
    nextLocation.includes('tableau') && validateCardBase(deck[first(cards)]);
  const isValidFoundationMove =
    nextLocation.includes('foundation') &&
    cards.length === 1 &&
    validateFoundationMove({
      destination: nextLocation as FoundationRowLocation,
      foundationCards: get({ foundation }, nextLocation, []) as CardId[],
      card: deck[first(cards)],
      deck,
    });

  return isValidFoundationMove || isValidTableauMove;
};

// Selectors
export const getNextMove = (state: State): Move => get(state, 'moves.nextMove', {});

export type State = State;
export default reducer;
