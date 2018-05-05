import * as range from 'lodash/fp/range';
import { Reducer, ActionCreator, ActionThunkCreator } from '../../types';
import {
  State,
  CardRefArray,
  Tableau,
  TableauRow,
  CardId,
  Deck,
} from './types';
import { get, cloneDeep } from 'lodash';
import { shuffleArray } from './utils';
import initialState from './initialState';
import { dealTableauCards, turnCards } from './utils';

// Actions
export const DEALCARDS = 'DEALCARDS';
export const DEALCARDS_INVALID = 'DEALCARDS_INVALID';
export const DEAL_HAND = 'DEAL_HAND';
export const RECYCLE_HAND = 'RECYCLE_HAND';

const reducer: Reducer<State> = (state = initialState, action) => {
  switch (action.type) {
    case DEALCARDS: {
      const { deck, dealt } = state;

      const shuffledDeck = shuffleArray(Object.keys(deck));

      const tableauCards = shuffledDeck.slice(0, 28);
      const stockPile = shuffledDeck.slice(28);

      const tableau = dealTableauCards(tableauCards, cloneDeep(state.tableau));
      // TODO - encapsulate in a function
      const cardsToTurn = Object.values(tableau)
        .map(value => value.slice(-1))
        .reduce((acc, arr) => acc.concat(arr), []);

      return {
        ...state,
        deck: turnCards(cardsToTurn, deck),
        dealt: true,
        tableau,
        stock: stockPile,
      };
    }
    case DEAL_HAND: {
      const { deck, hand, stock } = state;
      const HAND_SIZE = 3;

      const newHandCards = stock.slice(0, HAND_SIZE);
      return {
        ...state,
        deck: turnCards(newHandCards, deck),
        hand: hand.concat(newHandCards),
        stock: stock.slice(HAND_SIZE),
      };
    }
    case RECYCLE_HAND:
      const { deck, hand, stock } = state;

      return {
        ...state,
        deck: turnCards(hand, deck, false),
        stock: stock.concat(hand),
        hand: [],
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

// deal from deck to hand
export const dealHand: ActionCreator = () => ({
  type: DEAL_HAND,
});

// recycle the hand back into the deck
export const recycleHand: ActionCreator = () => ({ type: RECYCLE_HAND });

// move a single card / group of cards to a tableau row
// --> will need to include both the location the card is currently in & the tableau row it is going to
// move a single card to the foundation
// --> will need to include the location the card is currently in as well as the card ID

// Selectors
export const getDealt = (state: State) => get(state, 'cards.dealt');
export const getDeck = (state: State) => get(state, 'cards.deck');
export const getTableau = (state: State) => get(state, 'cards.tableau');
export const getStock = (state: State) => get(state, 'cards.stock');

export type State = State;
export default reducer;
