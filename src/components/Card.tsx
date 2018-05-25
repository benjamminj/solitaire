import * as React from 'react';
import { Suit, CardRank } from '../store/modules/cards/types';
import * as cx from 'classnames';

type Props = {
  className?: string;
  visible: boolean;
  suit: Suit;
  rank: CardRank;
};

type GetCardStyles = (p: Props) => string;
// TODO -- make the background themeable, perhaps by using something like color-primary
const getCardStyles: GetCardStyles = props =>
  (props.visible ? 'bg-white border-blue' : 'bg-blue border-transparent');

const Card: React.SFC<Props> = props => (
  <button
    className={cx(
      getCardStyles(props),
      'border-solid',
      'border',
      props.className,
    )}
  >
    {props.visible ? (
      <span>
        <span>
          {props.suit[0]}&ndash;{props.rank}
        </span>
      </span>
    ) : (
      <span />
    )}
  </button>
);

export default Card;
