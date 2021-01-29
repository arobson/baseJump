require('./setup');
const jump = require('../src/baseJump.js');

describe('base36', function () {
  describe('with default padding', function () {
    const defaultPadding = jump.toBase36([1, 1, 1, 1, 1, 1, 1, 1, 1]);

    it('should produce a 26 character id', function () {
      defaultPadding.length.should.equal(26);
    });

    it('should 0 pad to the left', function () {
      defaultPadding.should.equal('00000000000003WP6BHASGO269');
    });
  });

  describe('with decreased padding', function () {
    const decreasedPadding = jump.toBase36([100, 100, 200], 10);

    it('should produce a 10 character id', function () {
      decreasedPadding.length.should.equal(10);
    });

    it('should truncate to the left', function () {
      decreasedPadding.should.equal('000007THES');
    });
  });

  describe('with insufficient padding', function () {
    const insufficientPadding = jump.toBase36([100, 100, 200], 2);

    it('should produce a 2 character id', function () {
      insufficientPadding.length.should.equal(2);
    });

    it('should truncate to the left', function () {
      insufficientPadding.should.equal('ES');
    });
  });
});

describe('base62', function () {
  describe('with default padding', function () {
    const defaultPadding = jump.toBase62([1, 1, 1, 1, 1, 1, 1, 1, 1]);

    it('should produce a 22 character id', function () {
      defaultPadding.length.should.equal(22);
    });

    it('should 0 pad to the left', function () {
      defaultPadding.should.equal('00000000000M41bLKJJnxR');
    });
  });

  describe('with decreased padding', function () {
    const decreasedPadding = jump.toBase62([100, 100, 200], 10);

    it('should produce a 10 character id', function () {
      decreasedPadding.length.should.equal(10);
    });

    it('should truncate to the left', function () {
      decreasedPadding.should.equal('000000t6Sy');
    });
  });

  describe('with insufficient padding', function () {
    const insufficientPadding = jump.toBase62([100, 100, 200], 2);

    it('should produce a 2 character id', function () {
      insufficientPadding.length.should.equal(2);
    });

    it('should truncate to the left', function () {
      insufficientPadding.should.equal('Sy');
    });
  });
});
