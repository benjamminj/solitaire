import { combineReducers } from 'redux';

import cards, { State as CardState } from './modules/cards';

export type State = {
  cards: CardState;
};
export default combineReducers({ cards });
