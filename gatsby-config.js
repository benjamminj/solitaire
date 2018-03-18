module.exports = {
  siteMetadata: {
    title: 'Gatsby Default Starter',
  },
  plugins: [
    'gatsby-plugin-react-helmet',
    `gatsby-plugin-react-next`,
    {
      resolve: 'gatsby-plugin-typescript',
      options: {
        transpileOnly: true, // default
        compilerOptions: {
          target: `esnext`,
          experimentalDecorators: true,
          jsx: `react`
        } // default
      }
    }
  ],
};
