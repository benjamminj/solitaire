import * as React from 'react';
import Link from 'gatsby-link';
import { connect, DispatchProp } from 'react-redux';
import { State } from '../store/reducer';
import { shuffleDeck } from '../store/modules/cards';
import { ActionCreator } from 'redux';
import { ActionThunkCreator } from '../store/types';

type Props = {
  cards: State['cards'];
  shuffleDeck: ActionThunkCreator;
};

const IndexPage: React.SFC<Props> = (props: Props) => (
  <div className="p-4">
    now for solitaire!
    <div>
      <button
        className="bg-blue text-white p-2 my-2"
        onClick={props.shuffleDeck}
      >
        shuffle
      </button>
    </div>
    <div>
      <pre>
        <code>{JSON.stringify(props.cards, null, 4)}</code>
      </pre>
    </div>
  </div>
);

const mapStateToProps = (state: State) => ({ cards: state.cards });
const mapDispatchToProps = { shuffleDeck };

export default connect(mapStateToProps, mapDispatchToProps)(IndexPage);
