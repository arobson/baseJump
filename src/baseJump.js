const clib = require('../build/Release/baseJump');

module.exports = {
  toBase62: function (buffer, length) {
    return clib.to62(buffer, length || 22);
  },
  toBase36: function (buffer, length) {
    return clib.to36(buffer, length || 26);
  }
};
