import { pick } from 'lodash';
import reducer, { DEALCARDS, DEALCARDS_INVALID } from '../index';

describe('reducer', () => {
  // The DEALCARDS relies on randomness to shuffle the deck
  // This means we have to make looser assertions rather than using snapshots
  describe('DEALERCARDS', () => {
    test('should return tableau rows that are filled', () => {
      const { tableau } = reducer(undefined, { type: DEALCARDS });
      const entries = Object.entries(tableau);

      entries.forEach(([key, value]) => {
        expect(value.length).toEqual(+key);
      });
    });

    test('should return a `stock` with 24 cards', () => {
      const { stock } = reducer(undefined, { type: DEALCARDS });

      expect(stock.length).toEqual(24);
    });

    test('should enable the `dealt` flag', () => {
      const { dealt } = reducer(undefined, { type: DEALCARDS });

      expect(dealt).toEqual(true);
    });
  });

  test('should return the state for DEALCARDS_INVALID', () => {
    const result = reducer(undefined, { type: DEALCARDS_INVALID });
    expect(result).toMatchSnapshot();
  });
});
