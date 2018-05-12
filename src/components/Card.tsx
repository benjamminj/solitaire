import * as React from 'react';
import { Card as CardType } from '../store/modules/cards/types';
import * as cx from 'classnames';

type Props = CardType;

type GetCardStyles = (p: Props) => string;
// TODO -- make the background themeable, perhaps by using something like color-primary
const getCardStyles: GetCardStyles = props =>
  (props.visible ? 'bg-white border-blue' : 'bg-blue border-transparent');

const Card: React.SFC<Props> = props => (
  <button className={cx(getCardStyles(props), 'border-solid', 'border', 'h-24')}>
    {props.visible ? (
      <span>
        <span>{props.suit}</span>
        <span>{props.rank}</span>
      </span>
    ) : (
      <span>hidden</span>
    )}
  </button>
);

export default Card;
