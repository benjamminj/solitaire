import * as React from 'react';
import { createRenderer } from 'react-test-renderer/shallow';
import Stock from '../Stock';
import initialState from '../../store/modules/cards/initialState';
import {
  mockConsoleError,
  restoreConsoleError,
} from '../../../test-utils/__mocks__/consoleError';

const renderer = createRenderer();

beforeAll(mockConsoleError);
afterAll(restoreConsoleError);

describe('Stock', () => {
  test('should render', () => {
    const tree = renderer.render(<Stock
      deck={initialState.deck}
      stock={['hearts-2', 'spades-K', 'diamonds-4', 'hearts-A']}
    />);

    expect(tree).toMatchSnapshot();
  });

  test('should render with an empty card if there is no length in the stock', () => {
    const tree = renderer.render(<Stock deck={initialState.deck} stock={[]} />);
  });
});
