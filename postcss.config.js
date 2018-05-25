const tailwindcss = require('tailwindcss');
const cssnext = require('postcss-cssnext');
// const postCssCustomProperties = require('postcss-custom-properties');
// const autoprefixer = require('autoprefixer');

module.exports = {
  plugins: [
    cssnext({
      features: {
        customProperties: false,
      },
    }),
    tailwindcss('./tailwind.js'),
  ],
};
