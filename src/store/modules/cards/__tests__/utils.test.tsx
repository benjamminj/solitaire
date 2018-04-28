import { dealTableauCards, shuffleArray } from '../utils';
import { range } from 'lodash';
import { Tableau } from '../types'

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
    '1': [],
    '2': [],
    '3': [],
    '4': [],
    '5': [],
    '6': [],
    '7': [],
  };

  test('should disperse the cards to the tableau rows', () => {
    const result = dealTableauCards(cards, tableau);
    expect(result).toMatchSnapshot();
  });
});