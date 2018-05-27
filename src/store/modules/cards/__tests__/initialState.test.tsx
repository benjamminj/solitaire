import {
  getInitialDeck,
  getInitialSuit,
  getRankFromRemainder,
} from '../initialState';

describe('getRankFromRemainder', () => {
  test('should return `K` if remainder === 0', () => {
    expect(getRankFromRemainder('0')).toEqual('K');
  });

  test('should return `Q` if remainder === 1', () => {
    expect(getRankFromRemainder('1')).toEqual('Q');
  });

  test('should return `J` if remainder === 2', () => {
    expect(getRankFromRemainder('2')).toEqual('J');
  });

  test('should return `A` if remainder === 12', () => {
    expect(getRankFromRemainder('12')).toEqual('A');
  });

  test('should return `13 - number` as a string in default case', () => {
    expect(getRankFromRemainder('9')).toEqual(`${13 - 9}`);
  });
});

describe('getInitialSuit', () => {
  test('should return an object', () => {
    expect(typeof getInitialSuit('hearts')).toEqual('object');
  });

  test('should have object keys that contain the suit name', () => {
    const result = getInitialSuit('spades');
    const keys = Object.keys(result);

    expect(keys.every(key => /spades/i.test(key))).toEqual(true);
  });
  test('should only have 13 keys', () => {
    const result = getInitialSuit('diamonds');
    const keys = Object.keys(result);
    expect(keys.length).toEqual(13);
  });

  test('should have key values that are a type of Card', () => {
    const result = getInitialSuit('spades');
    const card = result['spades-A'];
    expect(card).toMatchObject({
      id: 'spades-A',
      suit: 'spades',
      rank: 'A',
      value: 1,
      visible: false,
    });
  });
});

describe('getInitialDeck', () => {
  test('should return an object', () => {
    expect(typeof getInitialDeck()).toEqual('object');
  });

  test('should only contain 52 keys', () => {
    const result = getInitialDeck();
    const keys = Object.keys(result);
    expect(keys.length).toEqual(52);
  });

  test('should contain all 4 suits', () => {
    const result = getInitialDeck();
    const keys = Object.keys(result);
    expect(
      keys.every(key => /^(hearts-|clubs-|diamonds-|spades-)/.test(key))
    ).toEqual(true);
  });

  test('should have key values that are type of Card', () => {
    const result = getInitialDeck();
    const values = Object.values(result);

    values.forEach(val => {
      const keys = Object.keys(val);
      expect(keys.sort()).toEqual(['id', 'rank', 'suit', 'value', 'visible']);
    });
  });
});
