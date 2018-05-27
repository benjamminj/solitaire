module.exports = {
  roots: ['<rootDir>/src'],
  transform: {
    '^.+\\.tsx?$': 'ts-jest',
    '^.+\\.jsx?$': 'babel-jest',
  },
  /* moduleNameMapper: {
    '^react$': './node_modules/gatsby-plugin-react-next/node_modules/react',
    '^react-dom$': './node_modules/gatsby-plugin-react-next/node_modules/react-dom',
  }, */
  collectCoverageFrom: ['**/src/**/*.(js|ts|jsx|tsx)', '!**/node_modules/**'],
  testRegex: '(/__tests__/.*|(\\.|/)(test|spec))\\.tsx?$',
  moduleFileExtensions: ['ts', 'tsx', 'js', 'jsx', 'json', 'node'],
};
