require('./setup');
const jump = require('../src/baseJump.js');
const util = require('util');

describe('when converting bunches of buffers', function () {
  let list;
  let unique;
  let ms;
  before(function () {
    this.timeout(60000);
    list = [];
    const start = process.hrtime();
    for (let i = 0; i < 256; i++) {
      for (let j = 0; j < 256; j++) {
        list.push(jump.toBase62([j, i, 200, 100, 200, 50, 80, 11, 56, 210, 67, 87, 92]));
      }
    }

    const diff = process.hrtime(start);
    ms = (diff[0] * 1e9 + diff[1]) / 1000000;
    unique = _.uniq(list).length;
    console.log(`ok ${unique} in ${ms}`);
  });

  it('should be quick', function () {
    console.log(util.format('Created %d unique ids in %d ms for %d/ms', unique, ms, unique / ms));
    ms.should.be.lessThan(10000);
  });

  it('should generate only unique ids', function () {
    list.length.should.equal(unique);
  });
});
