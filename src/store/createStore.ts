import { applyMiddleware, createStore as reduxCreateStore, compose } from 'redux';
import { devToolsExtension } from './enhancers';
import { thunk } from './middleware';
import reducer from './reducer';

const createStore = () =>
  reduxCreateStore(reducer, compose(applyMiddleware(thunk), devToolsExtension));
export default createStore;
