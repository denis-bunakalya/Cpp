#include "controller.h"
#if 0
#include "gtest/gtest.h"

using namespace std;

TEST( UniverseTest, construct ) {

	vector< vector < bool > > cells;

	cells.resize( 1 );

	cells[ 0 ].resize( 1 );

	cells[ 0 ][ 0 ] = 1;

	bool birth[ 9 ] = { 0, 0, 0, 1, 0, 0, 0, 0, 0 };

	bool survival[ 9 ] = { 0, 0, 1, 1, 0, 0, 0, 0, 0 };

	Universe universe( "constructor_for_tests", string( "My universe" ), 1, 1, cells, birth, survival );

	ASSERT_EQ( "My universe", universe.get_universe_name() );

	for( int i = 0; i < 9; i++ ) {

	ASSERT_EQ( birth[ i ], universe.get_birth()[ i ] );

	ASSERT_EQ( survival[ i ], universe.get_survival()[ i ] );

	}

	ASSERT_EQ( 0, universe.get_current_iteration_number() );

	ASSERT_EQ( 1, universe.get_width() );

	ASSERT_EQ( 1, universe.get_height() );

	ASSERT_EQ( cells, universe.get_field()->get_cells() );

}

TEST( UniverseTest, next ) {

	vector< vector < bool > > cells;

	cells.resize( 1 );

	cells[ 0 ].resize( 2 );

	cells[ 0 ][ 0 ] = 0;

	cells[ 0 ][ 1 ] = 1;

	bool birth[ 9 ] = { 0, 0, 0, 1, 0, 0, 0, 0, 0 };

	bool survival[ 9 ] = { 0, 0, 1, 1, 0, 0, 0, 0, 0 };

	Universe universe( "constructor_for_tests", string( "My universe" ), 2, 1, cells, birth, survival );

	universe.next();

	ASSERT_EQ( "My universe", universe.get_universe_name() );

	for( int i = 0; i < 9; i++ ) {

	ASSERT_EQ( birth[ i ], universe.get_birth()[ i ] );

	ASSERT_EQ( survival[ i ], universe.get_survival()[ i ] );

	}

	ASSERT_EQ( 1, universe.get_current_iteration_number() );

	ASSERT_EQ( 2, universe.get_width() );

	ASSERT_EQ( 1, universe.get_height() );

	ASSERT_EQ( cells, universe.get_field()->get_cells() );

}
#endif
int main( int argc, char** argv ){	

	/*::testing::InitGoogleTest( &argc, argv );

    return RUN_ALL_TESTS();*/

	try {

	Controller controller ( argc, argv );

	} catch ( ... ) {

		exit( 1 );

	}

	return 0;

}
