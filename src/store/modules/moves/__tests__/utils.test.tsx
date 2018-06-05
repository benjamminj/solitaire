import { validateMove } from '../utils';
import initialState from '../../cards/initialState';

const { deck, foundation, tableau } = initialState;

describe('validateMove', () => {
  test('should return false if the next location doesnt include `tableau` or `foundation`', () => {
    const result = validateMove({
      nextLocation: 'hand',
      cards: ['diamonds-A'],
      deck,
      foundation,
      tableau,
    });

    expect(result).toEqual(false);
  });

  test('should return false if the tableau validation fails', () => {
    const result = validateMove({
      cards: ['spades-2'],
      nextLocation: 'tableau.3',
      deck,
      foundation,
      tableau: {
        ...tableau,
        3: ['hearts-2'],
      },
    });

    expect(result).toEqual(false);
  });

  test('should return true if the tableau validation passes', () => {
    const result = validateMove({
      cards: ['spades-2'],
      nextLocation: 'tableau.3',
      deck,
      foundation,
      tableau: {
        ...tableau,
        3: ['hearts-3'],
      },
    });

    expect(result).toEqual(true);
  });

  test('should return false when moving > 1 cards to foundation', () => {
    const result = validateMove({
      cards: ['diamonds-3', 'diamonds-4'],
      nextLocation: 'foundation.diamonds',
      deck,
      foundation: {
        ...foundation,
        diamonds: ['diamonds-1', 'diamonds-2'],
      },
      tableau,
    });

    expect(result).toEqual(false);
  });

  test('should return false when card to foundation that is a different suit', () => {
    const result = validateMove({
      cards: ['spades-3'],
      nextLocation: 'foundation.diamonds',
      deck,
      foundation: {
        ...foundation,
        diamonds: ['diamonds-1', 'diamonds-2'],
      },
      tableau,
    });

    expect(result).toEqual(false);
  });

  test('should return false when card to foundation that is not +1 in rank', () => {
    const result = validateMove({
      cards: ['diamonds-5'],
      nextLocation: 'foundation.diamonds',
      deck,
      foundation: {
        ...foundation,
        diamonds: ['diamonds-1', 'diamonds-2'],
      },
      tableau,
    });

    expect(result).toEqual(false);
  });

  test('should return true when card passes validation to foundation', () => {
    const result = validateMove({
      cards: ['diamonds-3'],
      nextLocation: 'foundation.diamonds',
      deck,
      foundation: {
        ...foundation,
        diamonds: ['diamonds-1', 'diamonds-2'],
      },
      tableau,
    });

    expect(result).toEqual(true);
  });

  test('should return true when passing an Ace to an empty foundation', () => {
    const result = validateMove({
      cards: ['diamonds-A'],
      nextLocation: 'foundation.diamonds',
      deck,
      foundation: {
        ...foundation,
        diamonds: [],
      },
      tableau,
    });

    expect(result).toEqual(true);
  });
});
