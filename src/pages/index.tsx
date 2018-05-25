import * as React from 'react';
import Link from 'gatsby-link';
import { connect, DispatchProp } from 'react-redux';
import { State } from '../store/reducer';
import { dealCards, dealHand } from '../store/modules/cards';
import { ActionThunkCreator, ActionCreator } from '../store/types';
import Card from '../components/Card';
import { CardId, Deck } from '../store/modules/cards/types';

const buttonClasses = ({ text = 'white', bg = 'blue' } = {}) =>
  `bg-${bg} text-${text} p-2 m-0 sm:mr-2 w-full sm:w-auto`;

type Props = {
  cards: State['cards'];
  dealCards: ActionThunkCreator;
  dealHand: ActionCreator;
};

// TODO -- make a new component to handle the mapping and keep this clean (:
const CardGroup: React.SFC<{ cardIds: CardId[]; deck: Deck }> = ({
  cardIds,
  deck,
}) => cardIds.map(id => <Card key={id} {...deck[id]} />);

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

    <h2>tableau</h2>
    <div
      style={{
        '--grid-template-columns': 'repeat(7, 1fr)',
      }}
      className="grid grid-template-columns grid-gap-1"
    >
      {Object.entries(props.cards.tableau).map(([row, cards]) => (
        <div
          style={{
            '--grid-template-columns': '1fr',
            gridAutoRows: '75px',
          }}
          className="grid grid-template-columns grid-gap-1"
        >
          <CardGroup key={row} cardIds={cards} deck={props.cards.deck} />
        </div>
      ))}
      {/* {Object.entries(props.cards.deck).map(([key, card]) => (
        <Card key={key} {...card} />
      ))} */}
    </div>
  </div>
);

const mapStateToProps = (state: State) => ({ cards: state.cards });
const mapDispatchToProps = { dealCards, dealHand };

export default connect(mapStateToProps, mapDispatchToProps)(IndexPage);
