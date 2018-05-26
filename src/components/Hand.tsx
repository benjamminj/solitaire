import * as React from 'react';
import CardGroup from './CardGroup';
import { Hand, Deck } from '../store/modules/cards/types';
import * as cx from 'classnames'

type Props = {
  className?: string;
  style?: { [key: string]: string };
  hand: Hand;
  deck: Deck;
};

const HandComponent: React.SFC<Props> = ({
  hand, deck, className, style,
}) => (
  <div className={cx(className, 'grid-auto-rows-24')} style={style}>
    {hand.length ? (
      <CardGroup className="h-24 w-1/3" cardIds={hand.slice(-3)} deck={deck} />
    ) : null}
  </div>
);

export default HandComponent;
