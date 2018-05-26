import * as React from 'react';
import { render } from 'react-testing-library';
import { createRenderer } from 'react-test-renderer/shallow';
import Hand from '../Hand';
import initialState from '../../store/modules/cards/initialState';

const renderer = createRenderer();

describe('Hand', () => {
  test('should render', () => {
    const tree = renderer.render(<Hand
      hand={['spades-2', 'diamonds-4', 'hearts-9', 'clubs-K']}
      deck={initialState.deck}
    />);

    expect(tree).toMatchSnapshot();
  });

  test('should render nothing if there is no length to the hand', () => {
    const tree = renderer.render(<Hand deck={initialState.deck} hand={[]} />);

    expect(tree).toMatchSnapshot();
  });
});
