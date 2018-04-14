import { applyMiddleware, compose } from 'redux';

type WindowWithExtension = Window & {
  __REDUX_DEVTOOLS_EXTENSION__?: () => {};
};

export default () => {
  if (process.env.NODE_ENV === 'development') {
    const windowWithExtension = <WindowWithExtension>window;
    
    return (
      windowWithExtension.__REDUX_DEVTOOLS_EXTENSION__ &&
      windowWithExtension.__REDUX_DEVTOOLS_EXTENSION__()
    );
  }
};
