import { pick, cloneDeep } from 'lodash';
import initialState from '../initialState';
import { State } from '../types';
import reducer, { DEALCARDS, DEALCARDS_INVALID, DEAL_HAND } from '../index';

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

  describe('DEALERCARDS_INVALID', () => {
    test('should return the state', () => {
      const result = reducer(undefined, { type: DEALCARDS_INVALID });
      expect(result).toMatchSnapshot();
    });
  });

  describe('DEAL_HAND', () => {
    const state = {
      ...cloneDeep(initialState),
      stock: [
        'hearts-A',
        'hearts-2',
        'hearts-3',
        'hearts-4',
        'hearts-5',
        'hearts-6',
        'hearts-7',
        'hearts-8',
      ],
    };

    const action = { type: DEAL_HAND };
    test('should remove 3 cards from the front of the stock array', () => {
      const { stock } = reducer(state, action);
      expect(stock).toMatchSnapshot();
    });
    
    test('should add 3 cards to the beginning of the hand array', () => {
      const { hand } = reducer(state, action);
      expect(hand).toMatchSnapshot();
    })

    test('should not do anything if stock is empty', () => {
      const mockState: State = {
        ...cloneDeep(initialState),
        stock: [],
        hand: ['hearts-A']
      };

      const { hand, stock } = reducer(mockState, action)
      expect(stock).toEqual([])
      expect(hand).toEqual(['hearts-A'])
    }) 
  });
});
