import { range } from 'lodash/fp';
import {
  Reducer,
  Action,
  ActionCreator,
  ActionThunkCreator,
  ActionThunk,
} from '../../types';
import {
  State,
  Card,
  CardRefArray,
  Tableau,
  TableauRow,
  CardId,
  Deck,
  CardLocation,
  TableauRowLocation,
  Suit,
  FoundationRowLocation,
} from './types';
import { get, set, last, cloneDeep } from 'lodash';
import { shuffleArray, validateCardBase } from './utils';
import initialState from './initialState';
import { dealTableauCards, turnCards } from './utils';

// Actions
export const DEALCARDS = 'DEALCARDS';
export const DEALCARDS_INVALID = 'DEALCARDS_INVALID';
export const DEAL_HAND = 'DEAL_HAND';
export const RECYCLE_HAND = 'RECYCLE_HAND';
export const MOVE_CARDS_TO_TABLEAU = 'MOVE_CARDS_TO_TABLEAU';
export const MOVE_CARDS_TO_TABLEAU_INVALID = 'MOVE_CARDS_TO_TABLEAU_INVALID';
export const MOVE_CARD_TO_FOUNDATION = 'MOVE_CARD_TO_FOUNDATION';
// prettier-ignore
export const MOVE_CARD_TO_FOUNDATION_INVALID = 'MOVE_CARD_TO_FOUNDATION_INVALID';

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
    case RECYCLE_HAND: {
      const { deck, hand, stock } = state;

      return {
        ...state,
        deck: turnCards(hand, deck, false),
        stock: stock.concat(hand),
        hand: [],
      };
    }
    case MOVE_CARDS_TO_TABLEAU: {
      const { cards, currentLocation, destination } = action.result;
      const { deck } = state;

      const currentLocationCards = get(state, currentLocation, []);
      const destinationCards = get(state, destination, []);

      const nextState = cloneDeep(state);
      set(
        nextState,
        currentLocation,
        currentLocationCards.filter((card: CardId) => !cards.includes(card)),
      );
      set(nextState, destination, destinationCards.concat(cards));

      const currentRowWithoutCards = get(nextState, currentLocation);
      // will also need to turn over any cards at the end of the current row.
      return {
        ...nextState,
        deck: currentRowWithoutCards.length
          ? turnCards(
            [currentRowWithoutCards[currentRowWithoutCards.length - 1]],
            deck,
          )
          : deck,
      };
    }
    case MOVE_CARD_TO_FOUNDATION: {
      const { deck } = state;
      const { cardId, currentLocation, suit } = action.result;

      // remove the card from its current location
      const currentLocationCards = get(state, currentLocation, []);
      const suitCards = get(state.foundation, suit, []);

      const nextState = cloneDeep(state);
      set(nextState, 'foundation[suit]', suitCards.concat(cardId));
      set(nextState, currentLocation, currentLocationCards.slice(0, -1));

      const currentRowWithoutCards = get(nextState, currentLocation);

      return {
        ...nextState,
        deck: currentRowWithoutCards.length
          ? turnCards(
            [currentRowWithoutCards[currentRowWithoutCards.length - 1]],
            deck,
          )
          : deck,
      };
      // add the card to the suit
      // turn over the last card in the new current location
    }
    case DEALCARDS_INVALID:
    case MOVE_CARDS_TO_TABLEAU_INVALID:
    case MOVE_CARD_TO_FOUNDATION_INVALID:
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

export const dealHand: ActionCreator = () => ({ type: DEAL_HAND });
export const recycleHand: ActionCreator = () => ({ type: RECYCLE_HAND });

type MoveCardsToTableau = (
  cards: CardRefArray,
  currentLocation: CardLocation,
  destination: TableauRowLocation
) => ActionThunk;
export const moveCardsToTableau: MoveCardsToTableau = (
  cards,
  currentLocation,
  destination,
) => (dispatch, getState) => {
  const successAction = {
    type: MOVE_CARDS_TO_TABLEAU,
    result: { cards, currentLocation, destination },
  };
  const failureAction = {
    type: MOVE_CARDS_TO_TABLEAU_INVALID,
  };

  const state = getState();
  const { deck } = state;

  const currentCards = get(state, currentLocation);
  const destinationCards = get(state, destination);
  const firstCard = deck[cards[0]];
  const baseCard = deck[destinationCards[destinationCards.length - 1]];

  return validateCardBase(firstCard, baseCard) ? successAction : failureAction;
};

type MoveCardToFoundation = (
  cardId: CardId,
  currentLocation: CardLocation,
  suit: Suit
) => ActionThunk<State>;
export const moveCardToFoundation: MoveCardToFoundation = (
  cardId,
  currentLocation,
  suit,
) => (dispatch, getState) => {
  const { deck, foundation } = getState();
  const card = deck[cardId];

  const isSameSuit = card.suit === suit;

  const foundationRow = foundation[suit];
  const lastCardInFoundationRow = get(deck, last(foundationRow), { value: 0 });
  const isNextRank = card.value - 1 === lastCardInFoundationRow.value;

  return isNextRank && isSameSuit
    ? {
      type: MOVE_CARD_TO_FOUNDATION,
      cardId,
      currentLocation,
      suit,
    }
    : {
      type: MOVE_CARD_TO_FOUNDATION_INVALID,
    };
};

// Selectors
export const getDealt = (state: State) => get(state, 'cards.dealt');
export const getDeck = (state: State) => get(state, 'cards.deck');
export const getTableau = (state: State) => get(state, 'cards.tableau');
export const getStock = (state: State) => get(state, 'cards.stock');

export type State = State;
export default reducer;
