import { combineReducers } from 'redux';

import cards, { State as CardState } from './modules/cards';
import moves, { State as MovesState } from './modules/moves';

export type State = {
  cards: CardState;
  moves: MovesState
};

export default combineReducers({ cards, moves });
