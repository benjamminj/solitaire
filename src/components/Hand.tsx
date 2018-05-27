import * as React from 'react';
import Card from './Card';
import { Hand, Deck } from '../store/modules/cards/types';
import * as cx from 'classnames';
import { last, negate as not } from 'lodash';

type Props = {
  className?: string;
  style?: { [key: string]: string };
  hand: Hand;
  deck: Deck;
};

const isLast = (i: number, arr: any[]) => i + 1 === arr.length;
const isNotLast = not(isLast);

const HandComponent: React.SFC<Props> = ({ hand, deck, className, style }) => (
  <div
    className={cx(className, 'grid', 'grid-template-columns', 'h-24')}
    style={{ ...style, '--grid-template-columns': '1fr 1fr' }}
  >
    {hand.length
      ? hand.slice(-3).map((cardId, i, arr) => (
          <Card
            disabled={isNotLast(i, arr)}
            className={cx(
              'grid-column',
              'grid-row',
              'relative',
              {
                'right-neg-1/4': i !== 0 && isNotLast(i, arr),
              },
              `z-${i + 1}0` // z-10, z-20, z-30, etc.
            )}
            style={{
              '--grid-column': isLast(i, arr) ? '2' : '1',
              '--grid-row': '1',
            }}
            key={cardId}
            {...deck[cardId]}
          />
        ))
      : null}
  </div>
);

export default HandComponent;
