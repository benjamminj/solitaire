import path from 'path'

const root = path.join(__dirname, '../')

export default {
  entry: path.join(root, 'src/index.js'),
  output: {
    filename: 'bundle.js',
    path: path.join(root, 'dist')
  },
  module: {
    rules: [
      {
        test: /\.js$/,
        exclude: /node_modules/,
        use: 'babel-loader'
      }
    ]
  }
}
