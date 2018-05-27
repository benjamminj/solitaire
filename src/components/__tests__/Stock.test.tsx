import * as React from 'react';
import { createRenderer } from 'react-test-renderer/shallow';
import { render, renderIntoDocument, fireEvent } from 'react-testing-library';
import Stock from '../Stock';
import initialState from '../../store/modules/cards/initialState';
import { prettyDOM } from 'dom-testing-library';

const renderer = createRenderer();

describe('Stock', () => {
  test('should render', () => {
    const tree = renderer.render(
      <Stock
        deck={initialState.deck}
        stock={['hearts-2', 'spades-K', 'diamonds-4', 'hearts-A']}
      />
    );

    expect(tree).toMatchSnapshot();
  });

  test('should render with an empty card if there is no length in the stock', () => {
    const tree = renderer.render(<Stock deck={initialState.deck} stock={[]} />);
  });

  test('should trigger onClickCard function when cards are clicked', () => {
    const onClickCard = jest.fn();
    const { getByTestId } = renderIntoDocument(
      <Stock
        deck={initialState.deck}
        stock={['hearts-A']}
        onClickCard={onClickCard}
      />
    );

    const card = getByTestId(/hearts-A/);

    fireEvent.click(card);

    expect(onClickCard).toBeCalled();
  });

  test('should trigger onClickEmpty if empty card is clicked', () => {
    const onClickEmpty = jest.fn();
    
    const { getByTestId } = renderIntoDocument(
      <Stock deck={initialState.deck} stock={[]} onClickEmpty={onClickEmpty} />
    );

    fireEvent.click(getByTestId('EmptyCard'));
    expect(onClickEmpty).toBeCalled();
  });
});
