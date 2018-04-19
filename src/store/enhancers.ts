type WindowWithExtension = Window & {
  __REDUX_DEVTOOLS_EXTENSION__?: () => {};
};

export const devToolsExtension = () => {
  if (process.env.NODE_ENV === 'development') {
    const windowWithExtension = window as WindowWithExtension;
    
    return (
      windowWithExtension.__REDUX_DEVTOOLS_EXTENSION__ &&
      windowWithExtension.__REDUX_DEVTOOLS_EXTENSION__
    );
  }
};

