var gulp = require( 'gulp' );
var bg = require( 'biggulp' )( gulp );

gulp.task( 'test', bg.withCoverage() );
gulp.task( 'show-coverage', bg.showCoverage() );

gulp.task( 'default', [ 'test' ], function() {} );
