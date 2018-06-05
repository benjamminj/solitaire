import { CardId, CardLocation } from '../cards/types';

export type Move = {
  cards: CardId[];
  currentLocation?: CardLocation;
  destination?: CardLocation;
};

export type MoveId = string;

export type State = {
  nextMove: Move | {};
  // TODO -- may be able to remove entirely, since the only operations to the history are actually removing actions / undo
  moves: {
    [id: string]: Move;
  };
  history: Move[];
};
