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
  onClickCard?: React.EventHandler<React.MouseEvent<any>>;
  onClickEmpty?: React.EventHandler<React.MouseEvent<any>>;
};

const StockComponent = (props: Props) => (
  <React.Fragment>
    {props.stock.length ? (
      <Card
        {...props.deck[last(props.stock)]}
        className="h-full w-full"
        onClick={props.onClickCard}
      />
    ) : (
      <EmptyCard onClick={props.onClickEmpty} />
    )}
  </React.Fragment>
);

export default StockComponent;
