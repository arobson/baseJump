var gulp = require( 'gulp' );
var bg = require( 'biggulp' )( gulp );

gulp.task( 'test', bg.withCoverage( '/baseJump.spec.js' ) );
gulp.task( 'show-coverage', bg.showCoverage( '/baseJump.spec.js' ) );
gulp.task( 'all', function() {
	return bg.test();
} );
gulp.task( 'default', [ 'test' ], function() {} );
