import * as React from 'react';
import { CardId, Deck } from '../store/modules/cards/types';
import Card from './Card';

type Props = {
  className?: string;
  style?: { [key: string]: string };
  cardIds: CardId[];
  deck: Deck;
  onClickCard?: (id: CardId) => void;
};

const CardGroup: React.SFC<Props> = ({
  className,
  cardIds,
  deck,
  style,
  onClickCard,
}) => (
  <React.Fragment>
    {cardIds.map((id: CardId) => (
      <Card
        onClick={() => (deck[id].visible ? onClickCard(id) : null)}
        className={className}
        style={style}
        key={id}
        {...deck[id]}
      />
    ))}
  </React.Fragment>
);

export default CardGroup;
