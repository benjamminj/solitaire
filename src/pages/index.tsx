import * as React from 'react';
import Link from 'gatsby-link';
import { connect, DispatchProp } from 'react-redux';
import { State } from '../store/reducer';
import { dealCards, dealHand } from '../store/modules/cards';
import { ActionThunkCreator, ActionCreator } from '../store/types';
import Card from '../components/Card';

const buttonClasses = ({ text = 'white', bg = 'blue' } = {}) =>
  `bg-${bg} text-${text} p-2 m-0 sm:mr-2 w-full sm:w-auto`;

type Props = {
  cards: State['cards'];
  dealCards: ActionThunkCreator;
  dealHand: ActionCreator;
};

const IndexPage: React.SFC<Props> = (props: Props) => (
  <div className="p-4">
    now for solitaire!
    <div className="my-2">
      <button className={buttonClasses()} onClick={props.dealCards}>
        deal cards
      </button>
      <button className={buttonClasses({ bg: 'red' })} onClick={props.dealHand}>
        deal hand from stock
      </button>
      <button
        className={buttonClasses({ bg: 'green' })}
        onClick={() => console.log(props.cards)}
      >
        log state.cards
      </button>
    </div>
    <div style={{ '--gt-columns': '1fr 1fr 1fr' }} className="grid gt-columns">
      {Object.entries(props.cards.deck).map(([key, card]) => (
        <Card key={key} {...card} />
      ))}
    </div>
  </div>
);

const mapStateToProps = (state: State) => ({ cards: state.cards });
const mapDispatchToProps = { dealCards, dealHand };

export default connect(mapStateToProps, mapDispatchToProps)(IndexPage);
