# baseJump

[![Build Status][travis-image]][travis-url]
[![Coverage Status][coveralls-image]][coveralls-url]
[![Version npm][version-image]][version-url]
[![npm Downloads][downloads-image]][downloads-url]
[![Dependencies][dependencies-image]][dependencies-url]

## Disclaimer
This project combines the 3 things I'm worst at:
 1. Math
 1. C++
 1. Computers

That said, I have verified the output against third party tools that will freely convert between different numeric bases. I did not include these in the tests because reasons.

## Huge Thanks To Matt McCutchen
I have one dependency that is included in this code, namely the venerable and blessed Matt Mccutchen's Big Integer Library. Matt graciously hosts this source at: http://mattmccutchen.net/bigint/. If you need Maths in C++, I recommend this over using OpenSSL's BigInteger lib.

## API
It's so easy even I can use it:

```javascript
var jump = require( 'baseJump' );

// Node buffers can be treated as / thought of as an array of 8 bit numbers.
// Don't believe me? Call buffer.toJSON somtime. Anyway, passing one of those
// arrays to baseJump is how we pass along data.
var one = jump.toBase62( [ 100, 100, 200 ] );

// one == '000000000000000000t6Sy'
// Because of my own selfish selfishness, it auto-pads to 22 characters since that's
// the max number of characters required to represent a 128 bit unsigned integer. Maybe. Who knows.
// Certainly not me. Math is hard.
// The good news is you can control this:
var two = jump.toBase62( [ 100, 100, 200 ], 10 );

// two == '000000t6Sy' Easy.

// And base 36 calls work the same, btw, toBase36 defaults to 26 spaces.
var three = jump.toBase36( [ 100, 100, 200 ], 10 );

// three == '000007THES' ta-da
```

## Frequently Imagined Questions (FIQ)

### How Do I Get This Crap To Install on Windows
You'll need a pre-3.0 Python version installed an in your PATH.
You'll also need a C++ compiler. This will be annoying to set up if you don't have one. But you're on Windows and that's just how they do.

 * [VS 2010 C++ Express](http://go.microsoft.com/?linkid=9709949)
 * [VS 2010 SP1](http://www.microsoft.com/en-us/download/confirmation.aspx?id=23691) - why isn't this just in the download? So that everything they do will remain a consistent hot bucket of non-sense :)

### Why?
Flake ids should be 128 bits as the good Boundary intended. Or whoever came up with it. Anyway, I want flake ids and I want them today and in 128 bits and rendered as base 62 encoded, lexicograhpically sortable strings. And I want it to be as fast as possible. That is the only reason anyone should ever hurt themselves with C++.

### BaseJump?
Yeah. So. Take the code and call it something else. If other people ask me, I might be able to add different base conversions. I tried to make it so it'd be easy for me. But I see a lot of folks asking for 62 and 36 and almost nothing supports either (in Node anyway) or does it sloooooowwwwwllllyyyyy.

### Why Didn't You Just Use [some other thing]
I tried. Those other things were slow and/or irritating and/or required a ton of dependencies.

[travis-image]: https://travis-ci.org/arobson/basejump.svg?branch=master
[travis-url]: https://travis-ci.org/arobson/basejump
[coveralls-url]: https://coveralls.io/github/arobson/basejump?branch=master
[coveralls-image]: https://coveralls.io/repos/github/arobson/basejump/badge.svg?branch=master
[version-image]: https://img.shields.io/npm/v/basejump.svg?style=flat
[version-url]: https://www.npmjs.com/package/basejump
[downloads-image]: https://img.shields.io/npm/dm/basejump.svg?style=flat
[downloads-url]: https://www.npmjs.com/package/basejump
[dependencies-image]: https://img.shields.io/david/arobson/basejump.svg?style=flat
[dependencies-url]: https://david-dm.org/arobson/basejump
