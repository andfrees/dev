var webpack = require("webpack");

module.exports = {
    entry: ["./entry.js"],
    output: {
        path: __dirname + '/dist',
        filename: "bundle.js"
    },
    module: {
        loaders: [{
           test:/\.css$/,
           exclude: /node_modules/,
           loader:'style-loader!css-loader' 
        }],
        rules: [
            {test: /.js$/, use: ['babel-loader']},
            {test: /.css$/, use: ['style-loader', 'css-loader']},
            {test: /.(jpg|png|gif|svg)$/, use: ['url-loader?limit=8192&name=./[name].[ext]']},
            {test: /.less$/, use: ['style-loader', 'css-loader', 'less-loader']}
        ]
    },
    resolve: {
        extensions: ['.js', '.json', '.css', '.scss']
    },
    //https://github.com/webpack/docs/wiki/Configuration
    node: {
      fs: "empty",
      net: "empty"
    },
    plugins: [
        new webpack.BannerPlugin("This file is created by and")
        //new webpack.optimize.UglifyJsPlugin()
    ]
}

