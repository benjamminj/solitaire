// TODO - figure out how to type this redux middleware
// prettier-ignore
export const thunk = store => next => action =>
  (typeof action === 'function'
    ? next(action(store.dispatch, store.getState))
    : next(action));
