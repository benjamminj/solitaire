// Generic Redux-related types
export type Action = {
  type: string;
  result: {
    [x: string]: any
  }
}

export type ActionCreator = (...args: any[]) => Action

export type Reducer<T> = (state: T, action: Action) => T