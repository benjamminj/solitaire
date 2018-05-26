import * as React from 'react';
import { Deck, Stock } from '../store/modules/cards/types';
import Card from './Card';
import EmptyCard from './EmptyCard';
import { last } from 'lodash';

type Props = {
  className?: string;
  style?: { [key: string]: string };
  deck: Deck;
  stock: Stock;
};

const StockComponent = (props: Props) => (
  <div className={props.className} style={props.style}>
    {props.stock.length ? (
      <Card {...props.deck[last(props.stock)]} className="h-full w-full" />
    ) : (
      <EmptyCard />
    )}
  </div>
);

export default StockComponent;
