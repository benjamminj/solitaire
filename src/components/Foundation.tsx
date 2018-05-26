import * as React from 'react';
import { Foundation, Deck } from '../store/modules/cards/types';
import Card from './Card';
import EmptyCard from './EmptyCard';
import { last } from 'lodash';
import * as cx from 'classnames';

type Props = {
  className?: string;
  style?: { [key: string]: string };
  foundation: Foundation;
  deck: Deck;
};

const Foundation = (props: Props) => (
  <div
    className={cx(
      props.className,
      'grid',
      'grid-template-columns',
      'grid-gap-1',
      'grid-auto-rows-24',
    )}
    style={{ ...props.style, '--grid-template-columns': 'repeat(4, 1fr)' }}
  >
    {Object.entries(props.foundation).map(([name, row], i) =>
        (row.length ? (
          <Card key={i} {...props.deck[last(row)]} />
        ) : (
          <EmptyCard key={i} />
        )))}
  </div>
);

export default Foundation;
