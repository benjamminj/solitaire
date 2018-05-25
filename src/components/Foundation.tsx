import * as React from 'react';
import { Foundation, Deck } from '../store/modules/cards/types';
import Card from './Card';
import EmptyCard from './EmptyCard';
import { last } from 'lodash';

type Props = {
  foundation: Foundation;
  deck: Deck;
};

const Foundation = (props: Props) => (
  <React.Fragment>
    <h2>foundation</h2>

    <div className="flex">
      {Object.entries(props.foundation).map(([name, row], i) =>
          (row.length ? (
            <Card key={i} {...props.deck[last(row)]} />
          ) : (
            <EmptyCard key={i} />
          )))}
    </div>
  </React.Fragment>
);

export default Foundation;
