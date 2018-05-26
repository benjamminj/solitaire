/* eslint-disable no-console */
/**
 * Intended for mocking out the console error to keep test output clean. For example,
 * right now some components that export a React Fragment will throw errors in the console
 * because the test renderer evaluates them to `UNDEFINED`.
 * 
 * This shouldn't be a long term solution, so the presence of this utility in a test file is
 * an indication that the source of the console errors (bad bael transformation, incorrect React version?)
 * should be researched.
 */
const originalError = console.error;

export const mockConsoleError = () => {
  console.error = () => {};
};

export const restoreConsoleError = () => {
  console.error = originalError;
};
