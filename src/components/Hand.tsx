import * as React from 'react';
import CardGroup from './CardGroup';
import { Hand, Deck } from '../store/modules/cards/types';

type Props = {
  hand: Hand;
  deck: Deck;
};

const HandComponent: React.SFC<Props> = ({ hand, deck }) => (
  <React.Fragment>
    <h2>hand</h2>
    <div>
      {hand.length ? (
        <CardGroup className="h-12 w-12" cardIds={hand.slice(-3)} deck={deck} />
      ) : null}
    </div>
  </React.Fragment>
);

export default HandComponent;
