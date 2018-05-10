// Generic Redux-related types
import { Store, Dispatch } from 'redux';

export type Action = {
  type: string;
  result?: {
    [x: string]: any;
  };
};

export type ActionCreator = (...args: any[]) => Action;

type GetState<T = any> = Store<T>['getState'];
export type ActionThunk<T = any> = (dispatch: Dispatch<Action>, getState: GetState<T>) => Action;

export type ActionThunkCreator = (...args: any[]) => ActionThunk;

export type Reducer < T > = (state: T, action: Action) => T;
