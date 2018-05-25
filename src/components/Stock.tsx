import * as React from 'react';
import { Deck, Stock } from '../store/modules/cards/types';
import Card from './Card';
import EmptyCard from './EmptyCard';
import { last } from 'lodash';

type Props = {
  deck: Deck;
  stock: Stock;
};

const StockComponent = (props: Props) => (
  <React.Fragment>
    <h2>stock</h2>
    <div>
      {props.stock.length ? (
        <Card {...props.deck[last(props.stock)]} className="h-12 w-12" />
      ) : (
        <EmptyCard />
      )}
    </div>
  </React.Fragment>
);

export default StockComponent;
