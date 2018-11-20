/**
 * Created by nxycd on 2018/11/20.
 */
const { invoke, hello } = require('./build/Release/nxmi.node');

module.exports = {
  'invoke': invoke,
  'hello':hello
}