/**
 * Implement Gatsby's Node APIs in this file.
 *
 * See: https://www.gatsbyjs.org/docs/node-apis/
 */

const postcssConfig = require('./postcss.config');

exports.modifyWebpackConfig = ({ config }) =>
  config.merge({
    postcss: postcssConfig,
  });
