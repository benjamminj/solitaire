import { pick, set, cloneDeep } from 'lodash';
import initialState from '../initialState';
import { Dispatch } from 'redux';
import { State } from '../types';
import reducer, {
  DEALCARDS,
  DEALCARDS_INVALID,
  DEAL_HAND,
  RECYCLE_HAND,
  moveCardsToTableau,
  moveCardToFoundation,
  MOVE_CARDS_TO_TABLEAU,
} from '../index';

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
    });

    test('should not do anything if stock is empty', () => {
      const mockState: State = {
        ...cloneDeep(initialState),
        stock: [],
        hand: ['hearts-A'],
      };

      const { hand, stock } = reducer(mockState, action);
      expect(stock).toEqual([]);
      expect(hand).toEqual(['hearts-A']);
    });

    test('should make cards in the hand visible', () => {
      const { deck, hand } = reducer(state, action);

      hand.forEach((cardId) => {
        expect(deck[cardId].visible).toEqual(true);
      });
    });
  });

  describe('RECYCLE_HAND', () => {
    const state = {
      ...cloneDeep(initialState),
      hand: ['diamonds-10', 'spades-2', 'clubs-K'],
    };

    const action = { type: RECYCLE_HAND };

    test('should empty the hand', () => {
      const { hand } = reducer(state, action);
      expect(hand).toEqual([]);
    });

    test('should move all cards in the hand to the stock', () => {
      const { stock } = reducer(state, action);
      expect(stock).toEqual(['diamonds-10', 'spades-2', 'clubs-K']);
    });

    test('should make all cards in the stock not visible', () => {
      const { deck, stock } = reducer(state, action);
      stock.forEach((cardId) => {
        expect(deck[cardId].visible).toEqual(false);
      });
    });
  });

  describe('MOVE_CARDS_TO_TABLEAU', () => {
    test('should move the cards to the end of the designated tableau row', () => {
      const state = cloneDeep(initialState);
      set(state, 'tableau.1', ['spades-4']);
      set(state, 'tableau.3', ['hearts-3']);

      const action = {
        type: MOVE_CARDS_TO_TABLEAU,
        result: {
          cards: ['hearts-3'],
          currentLocation: 'tableau.3',
          destination: 'tableau.1',
        },
      };

      const { tableau } = reducer(state, action);
      expect(tableau['1']).toMatchSnapshot()
    });

    test('should remove the cards from the current row if they are on the tableau', () => {
      const state = cloneDeep(initialState);
      set(state, 'tableau.1', ['spades-4']);
      set(state, 'tableau.3', ['hearts-3']);

      const action = {
        type: MOVE_CARDS_TO_TABLEAU,
        result: {
          cards: ['hearts-3'],
          currentLocation: 'tableau.3',
          destination: 'tableau.1',
        },
      };

      const { tableau } = reducer(state, action);
      expect(tableau['3']).toMatchSnapshot()
    });

    test('should remove the cards from the current row if they are on the foundation', () => {
      const state = cloneDeep(initialState);
      set(state, 'tableau.1', ['spades-4']);
      set(state, 'foundation.hearts', ['hearts-3']);

      const action = {
        type: MOVE_CARDS_TO_TABLEAU,
        result: {
          cards: ['hearts-3'],
          currentLocation: 'foundation.hearts',
          destination: 'tableau.1',
        },
      };

      const { foundation } = reducer(state, action);
      expect(foundation.hearts).toMatchSnapshot()
    });

    test('should remove the card from the hand if it is in the hand', () => {
      const state = cloneDeep(initialState);
      set(state, 'tableau.1', ['spades-4']);
      set(state, 'hand', ['hearts-3']);

      const action = {
        type: MOVE_CARDS_TO_TABLEAU,
        result: {
          cards: ['hearts-3'],
          currentLocation: 'hand',
          destination: 'tableau.1',
        },
      };

      const { hand } = reducer(state, action);
      expect(hand).toMatchSnapshot()
    });

    test('should make the new last card of the current row visible', () => {
      const state = cloneDeep(initialState);
      set(state, 'tableau.1', ['spades-4']);
      set(state, 'tableau.3', ['clubs-J', 'hearts-3']);

      const action = {
        type: MOVE_CARDS_TO_TABLEAU,
        result: {
          cards: ['hearts-3'],
          currentLocation: 'tableau.3',
          destination: 'tableau.1',
        },
      };

      const { deck } = reducer(state, action);
      expect(deck['clubs-J'].visible).toEqual(true)
    });
  });
});

describe('moveCardsToTableau', () => {
  test('should return thunk that returns valid action if cards are validated', () => {
    // clone state
    const state = cloneDeep(initialState);
    set(state, 'tableau.1', ['spades-7', 'hearts-3']);
    set(state, 'tableau.2', ['diamonds-5', 'spades-4']);
    // set tableau row 1
    // set tableau row 2

    const thunk = moveCardsToTableau(['hearts-3'], 'tableau.1', 'tableau.2');

    const getState = () => state;
    const dispatch = () => {};

    const result = thunk(dispatch as Dispatch<State>, getState);
    expect(result).toMatchSnapshot();
  });

  test('should return thunk that allows for moving multiple cards to a tableau row', () => {
    const state = cloneDeep(initialState);
    set(state, 'tableau.3', ['hearts-4', 'diamonds-3', 'spades-2']);
    set(state, 'tableau.6', ['clubs-5']);

    const thunk = moveCardsToTableau(
      ['hearts-4', 'diamonds-3', 'spades-2'],
      'tableau.3',
      'tableau.6',
    );
    const getState = () => state;
    const dispatch = () => {};
    const result = thunk(dispatch as Dispatch<State>, getState);

    expect(result).toMatchSnapshot();
  });

  test('should allow moving cards from foundation rows to the tableau', () => {
    const state = cloneDeep(initialState);
    set(state, 'foundation.hearts', [
      'hearts-A',
      'hearts-2',
      'hearts-3',
      'hearts-4',
    ]);
    set(state, 'tableau.5', ['diamonds-6', 'clubs-5']);

    const thunk = moveCardsToTableau(
      ['hearts-4'],
      'foundation.hearts',
      'tableau.5',
    );
    const getState = () => state;
    const dispatch = () => {};
    const result = thunk(dispatch as Dispatch<State>, getState);

    expect(result).toMatchSnapshot();
  });

  test('should allow moving cards from hand to the tableau', () => {
    const state = cloneDeep(initialState);
    set(state, 'tableau.5', ['spades-K', 'hearts-Q']);
    set(state, 'hand', ['hearts-A', 'clubs-6', 'spades-J']);

    const thunk = moveCardsToTableau(['spades-J'], 'hand', 'tableau.5');
    const getState = () => state;
    const dispatch = () => {};
    const result = thunk(dispatch as Dispatch<State>, getState);

    expect(result).toMatchSnapshot();
  });

  test('should return thunk that returns invalid action if cards are invalid', () => {
    const state = cloneDeep(initialState);
    set(state, 'tableau.5', ['spades-K', 'hearts-Q']);
    set(state, 'tableau.3', ['hearts-A', 'clubs-6', 'spades-2']);

    const thunk = moveCardsToTableau(['spades-2'], 'tableau.3', 'tableau.5');
    const getState = () => state;
    const dispatch = () => {};
    const result = thunk(dispatch as Dispatch<State>, getState);

    expect(result).toMatchSnapshot();
  });
});

describe('moveCardToFoundation', () => {
  test('should return a thunk which passes validation if the foundation row is empty and the card is an Ace', () => {
    const state = cloneDeep(initialState)
    set(state, 'tableau.3', ['hearts-3'])
    set(state, 'foundation.hearts', ['hearts-A', 'hearts-2'])

    const thunk = moveCardToFoundation('hearts-3', 'tableau.3', 'foundation.hearts')

    const getState = () => state;
    const dispatch = () => {}

    const result = thunk(dispatch as Dispatch<State>, getState)
    expect(result).toMatchSnapshot()
  })
  test('should return a thunk which passes validation if the foundation row is empty and the card is directly above the last card')
  test('should return a thunk which fails validation is the card is not the same suit as the foundation row')
  test('should return a thunk which fails validation if the card is not a value directly above the last card in the foundation row')
})
