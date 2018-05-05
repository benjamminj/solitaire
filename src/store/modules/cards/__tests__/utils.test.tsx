import initialState from '../initialState';
import { dealTableauCards, shuffleArray, turnCards } from '../utils';
import { set, cloneDeep, range } from 'lodash';
import { Deck, Tableau } from '../types';

describe('shuffleArray', () => {
  const arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
  test('should return an array', () => {
    // note - since this function uses Math.random under the hood,
    // I wonder if there's a chance that it could break. Look into what the
    // testing process is for things like this
    expect(shuffleArray(arr)).not.toEqual(arr);
  });
});

describe('dealTableauCards', () => {
  const cards = range(0, 25).map(num => `${num}`);
  const tableau: Tableau = {
    1: [],
    2: [],
    3: [],
    4: [],
    5: [],
    6: [],
    7: [],
  };

  test('should disperse the cards to the tableau rows', () => {
    const result = dealTableauCards(cards, tableau);
    expect(result).toMatchSnapshot();
  });
});

describe('turnCards', () => {
  const deck: Deck = {
    'hearts-A': {
      id: 'hearts-A',
      suit: 'hearts',
      rank: 'A',
      value: 1,
      visible: false,
    },
    'hearts-3': {
      id: 'hearts-3',
      suit: 'hearts',
      rank: '3',
      value: 3,
      visible: false,
    },
    'diamonds-10': {
      id: 'diamonds-10',
      suit: 'diamonds',
      rank: '10',
      value: 10,
      visible: false,
    },
    'spades-5': {
      id: 'spades-5',
      suit: 'spades',
      rank: '5',
      value: 5,
      visible: false,
    },
  };

  test('should make the cards with the matching IDs visible in the deck', () => {
    const result = turnCards(['hearts-A', 'diamonds-10'], deck);
    expect(result).toMatchSnapshot();
  });

  test('should allow turning cards to non-visible', () => {
    const mockDeck = cloneDeep(deck);
    set(mockDeck, 'hearts-A.visible', true);
    set(mockDeck, 'diamonds-10.visible', true);

    const result = turnCards(['hearts-A', 'diamonds-10'], deck);
    expect(result).toMatchSnapshot();
  });

  test('should not modify the deck passed in as an argument', () => {
    const result = turnCards(['hearts-A'], deck);
    expect(result).toMatchSnapshot();
  });
});
