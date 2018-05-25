import * as React from 'react';
import Link from 'gatsby-link';
import { connect, DispatchProp } from 'react-redux';
import { State } from '../store/reducer';
import { dealCards, dealHand, recycleHand } from '../store/modules/cards';
import { ActionThunkCreator, ActionCreator } from '../store/types';
import Card from '../components/Card';
import { CardId, Deck } from '../store/modules/cards/types';
import { last } from 'lodash';
import Foundation from '../components/Foundation';
import Stock from '../components/Stock';
import CardGroup from '../components/CardGroup';
import Hand from '../components/Hand';

const buttonClasses = ({ text = 'white', bg = 'blue' } = {}) =>
  `bg-${bg} text-${text} p-2 m-0 sm:mr-2 w-full sm:w-auto`;

type Props = {
  cards: State['cards'];
  dealCards: ActionThunkCreator;
  dealHand: ActionCreator;
  recycleHand: ActionCreator;
};

// TODO -- make a new component to handle the mapping and keep this clean (:
// const CardGroup: React.SFC<{
// className?: string;
// cardIds: CardId[];
// deck: Deck;
// }> = ({ className, cardIds, deck }) =>
//   cardIds.map(id => <Card className={className} key={id} {...deck[id]} />);

const EmptyCard: React.SFC<{}> = () => (
  <div className="border border-blue h-10 w-10" />
);

const IndexPage: React.SFC<Props> = (props: Props) => (
  <div className="p-4">
    now for solitaire!
    <div className="my-2 flex">
      <button className={buttonClasses()} onClick={props.dealCards}>
        deal cards
      </button>
      <button className={buttonClasses({ bg: 'red' })} onClick={props.dealHand}>
        deal hand
      </button>
      <button
        className={buttonClasses({ bg: 'purple' })}
        onClick={props.recycleHand}
      >
        recycle hand
      </button>
      <button
        className={buttonClasses({ bg: 'green' })}
        onClick={() => console.log(props.cards)}
      >
        log cards
      </button>
    </div>
    <div>
      <Foundation foundation={props.cards.foundation} deck={props.cards.deck} />
    </div>
    <div
      className="grid grid-template-columns"
      style={{ '--grid-template-columns': '1fr 1fr' }}
    >
      <div>
        <Stock deck={props.cards.deck} stock={props.cards.stock} />
      </div>
      <div>
        <Hand hand={props.cards.hand} deck={props.cards.deck}/>
      </div>
    </div>
    <div>
      <h2>tableau</h2>
      <div
        style={{
          '--grid-template-columns': 'repeat(7, 1fr)',
        }}
        className="grid grid-template-columns grid-gap-1"
      >
        {Object.entries(props.cards.tableau).map(([row, cards]) => (
          <div
            key={row}
            style={{
              '--grid-template-columns': '1fr',
              gridAutoRows: '75px',
            }}
            className="grid grid-template-columns grid-gap-1"
          >
            <CardGroup key={row} cardIds={cards} deck={props.cards.deck} />
          </div>
        ))}
      </div>
    </div>
  </div>
);

const mapStateToProps = (state: State) => ({ cards: state.cards });
const mapDispatchToProps = { dealCards, dealHand, recycleHand };

export default connect(mapStateToProps, mapDispatchToProps)(IndexPage);
