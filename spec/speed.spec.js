require( 'should' );
var jump = require( '../src/baseJump.js' );
var _ = require( 'lodash' );
var util = require( 'util' );

describe( 'when getting converting TONS of buffers ... (lol, not really tho)', function() {
	var list;
	var unique;
	var ms;
	before( function() {
		this.timeout( 60000 );
		list = [];
		var start = process.hrtime();
		for (i = 0; i < 256; i++)
			for (j = 0; j < 256; j++)
				//							1  2   3    4    5    6   7   8   9   10  11  12  13
				list.push( jump.toBase62( [ j, i, 200, 100, 200, 50, 80, 11, 56, 210, 67, 87, 92 ] ) );

		var diff = process.hrtime( start );
		ms = ( diff[ 0 ] * 1e9 + diff[ 1 ] ) / 1000000;
		unique = _.unique( list ).length;
	} );

	it( 'should be quick', function() {
		console.log( util.format( 'Created %d unique ids in %d ms for %d/ms', unique, ms, unique / ms ) );
		ms.should.be.lessThan( 10000 );
	} );

	it( 'should generate only unique ids', function() {
		list.length.should.equal( unique );
	} );
} );
