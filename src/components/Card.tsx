import * as React from 'react';
import { Suit, CardRank, CardId } from '../store/modules/cards/types';
import * as cx from 'classnames';

type Props = {
  disabled?: boolean;
  className?: string;
  style?: { [key: string]: string };
  visible: boolean;
  suit: Suit;
  id: CardId;
  rank: CardRank;
  onClick?: React.EventHandler<React.MouseEvent<HTMLButtonElement>>;
};

type GetCardStyles = (p: Props) => string;
// TODO -- make the background themeable, perhaps by using something like color-primary
const getCardStyles: GetCardStyles = props =>
  props.visible ? 'bg-white border-blue' : 'bg-blue border-transparent';

const Card: React.SFC<Props> = props => (
  <button
    data-testid={`Card__${props.id}`}
    onClick={props.onClick}
    disabled={props.disabled}
    style={props.style}
    className={cx(
      getCardStyles(props),
      'border-solid',
      'border',
      props.className
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
