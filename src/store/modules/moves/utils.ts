import {
  CardId,
  CardLocation,
  Deck,
  Foundation,
  FoundationRowLocation,
  Tableau,
} from '../cards/types';
import { validateCardBase, validateFoundationMove } from '../cards/utils';
import { first, get } from 'lodash';

// TODO -- perhaps this should be moved into the central `cards` reducer, & the side-effect is the logging of actions into history
type ValidateMove = (
  args: {
  cards: CardId[];
  nextLocation: CardLocation;
  deck: Deck;
  foundation: Foundation;
  tableau: Tableau;
  }
) => boolean;
export const validateMove: ValidateMove = ({
  cards,
  nextLocation,
  deck,
  foundation,
  tableau,
}) => {
  const isValidTableauMove =
    nextLocation.includes('tableau') &&
    validateCardBase(deck[first(cards)], deck[get({ tableau }, nextLocation, {})]);
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
