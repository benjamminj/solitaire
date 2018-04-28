import * as React from 'react';
import Link from 'gatsby-link';
import { connect, DispatchProp } from 'react-redux';
import { State } from '../store/reducer';
import { dealCards } from '../store/modules/cards';
import { ActionCreator } from 'redux';
import { ActionThunkCreator } from '../store/types';

type Props = {
  cards: State['cards'];
  dealCards: ActionThunkCreator;
};

const IndexPage: React.SFC<Props> = (props: Props) => (
  <div className="p-4">
    now for solitaire!
    <div className="my-2">
      <button
        className="bg-blue text-white p-2"
        onClick={props.dealCards}
      >
        deal cards
      </button>
      <button
        className="bg-green text-white p-2"
        onClick={() => console.log(props.cards)}
      >
        log state.cards
      </button>
    </div>
    <div />
  </div>
);

const mapStateToProps = (state: State) => ({ cards: state.cards });
const mapDispatchToProps = { dealCards };

export default connect(mapStateToProps, mapDispatchToProps)(IndexPage);
