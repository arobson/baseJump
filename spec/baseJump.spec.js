require( 'should' );
var jump = require( '../src/baseJump.js' );

describe( 'when ', function() {
	
} );

describe( 'when getting base 62 ids', function() {

	describe( 'with default padding', function() {
		var defaultPadding = jump.toBase62( [ 100, 100, 200 ] );

		it( 'should produce a 22 character id', function() {
			defaultPadding.length.should.equal( 22 );
		} );

		it( 'should 0 pad to the left', function() {
			defaultPadding.should.equal( '000000000000000000t6Sy' );
		} );
	} );

	describe( 'with decreased padding', function() {
		var decreasedPadding = jump.toBase62( [ 100, 100, 200 ], 10 );

		it( 'should produce a 10 character id', function() {
			decreasedPadding.length.should.equal( 10 );
		} );

		it( 'should truncate to the left', function() {
			decreasedPadding.should.equal( '000000t6Sy' );
		} );
	} );

	describe( 'with insufficient padding', function() {
		var insufficientPadding = jump.toBase62( [ 100, 100, 200 ], 2 );

		it( 'should produce a 2 character id', function() {
			insufficientPadding.length.should.equal( 2 );
		} );

		it( 'should truncate to the left', function() {
			insufficientPadding.should.equal( 'Sy' );
		} );
	} );

	describe( 'when getting converting TONS of buffers ... (lol, not really tho)', function() {
		var list = [];
		var start = process.hrtime();
		for( i = 0; i < 256; i ++ ) 
			for( j = 0; j < 256; j++ )
				list.push( jump.toBase62( [ j, i, 200, 100, 200, 50, 80 ] ) );
		
		var diff = process.hrtime( start );
		it( 'should be quick, yo', function() {
			var ms = ( diff[ 0 ] * 1e9 + diff[ 1 ] ) / 1000000;
			console.log( ms );
			ms.should.be.lessThan( 1 );
		} );
	} );
	


} );