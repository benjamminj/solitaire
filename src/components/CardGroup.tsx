import * as React from 'react';
import { CardId, Deck } from '../store/modules/cards/types';
import Card from './Card';

type Props = {
  className?: string;
  cardIds: CardId[];
  deck: Deck;
};

const CardGroup: React.SFC<Props> = ({ className, cardIds, deck }) => (
  <React.Fragment>
    {cardIds.map((id: CardId) => (
      <Card className={className} key={id} {...deck[id]} />
    ))}
  </React.Fragment>
);

export default CardGroup;
