import { CardId, CardLocation } from '../cards/types';

export type Move = {
  cards: CardId[];
  currentLocation?: CardLocation;
  destination?: CardLocation;
};

export type MoveId = string;

export type State = {
  nextMove: Move | {};
  moves: {
    [id: string]: Move;
  };
  history: Move[];
};
