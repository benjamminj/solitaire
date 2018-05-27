import * as React from 'react';
import * as cx from 'classnames';
import CardGroup from './CardGroup';
import { Deck, Tableau } from '../store/modules/cards/types';

type Props = {
  className?: string;
  tableau: Tableau;
  deck: Deck;
};

const TableauComponent: React.SFC<Props> = ({ className, deck, tableau }) => (
  <div
    style={
      {
        '--grid-template-columns': 'repeat(7, 1fr)',
      } as React.CSSProperties
    }
    className={cx(className, 'grid', 'grid-template-columns', 'grid-gap-1')}
  >
    {Object.entries(tableau).map(([row, cards]) => (
      <div key={row} className="grid grid-gap-1 grid-auto-rows-24">
        <CardGroup
          key={row}
          className="h-24 w-100"
          cardIds={cards}
          deck={deck}
        />
      </div>
    ))}
  </div>
);

export default TableauComponent;
