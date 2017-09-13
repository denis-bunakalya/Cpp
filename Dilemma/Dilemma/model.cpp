#include <fstream>

#include "model.h"
#include "factory.h"
#include "controller.h"
#include "tournament.h"

Model::Model( int argc, char** argv ) : game_mode( detailed ) {

	if ( 4 > argc ) {

		throw std::exception();

	} 

	std::vector< std::string > strategies_;	

	std::vector< std::string >::iterator it = strategies_.end();

	bool game_mode_setted = false;

	std::string arg;

	int steps = 0;

	bool steps_setted = false;

	bool matrix_setted = false;

	for( int i = 1; i < argc; i++ ) {

		arg = argv[ i ];

		if ( !game_mode_setted && ( "-mode=detailed" == arg ) ) {

			game_mode = detailed;

			game_mode_setted = true;

		} else if ( !game_mode_setted && ( "-mode=fast" == arg ) ) {

			game_mode = fast;

			game_mode_setted = true;

		} else if ( !game_mode_setted && ( "-mode=tournament" == arg ) ) {

			game_mode = tournament;

			game_mode_setted = true;

		} else if ( !steps_setted && ( 7 < arg.length() ) && ( "-steps=" == arg.substr( 0, 7 ) ) ) {

			if ( !Controller::read_number_of_steps( arg.substr( 7, arg.length() - 7 ), &steps ) ) {

				throw std::exception();

			}

			steps_setted = true;

		} else if ( ( 8 < arg.length() ) && ( "-matrix=" == arg.substr( 0, 8 ) ) ) {

			try {

				read_matrix( arg.substr( 8, arg.length() - 8 ) );

			} catch (...) {

				throw;

			}

			matrix_setted = true;

		} else if ( Factory::instance()->get_creators().end() != 

			Factory::instance()->get_creators().find( argv[ i ] ) ) {

				strategies_.insert( it, argv[ i ] );

				it=strategies_.end();

		} else {

			throw std::exception();

		} 

	}

	if ( ( 3 > strategies_.size() ) || ( ( ( 3 < strategies_.size() ) || steps_setted )

		&& ( game_mode_setted && ( tournament != game_mode ) || !steps_setted ) ) ) {

			throw std::exception();

	}

	if ( ( 3 < strategies_.size() ) || steps_setted ) {

		game_mode = tournament;

	}

	if ( game_mode == tournament ) {

		Tournament tournament( strategies_, steps );

	} else {

		create_model( strategies_ );

	}

}

Model::Model( std::vector< std::string >& strategies_ ) {	

	create_model( strategies_ );	

}

void Model::create_model( std::vector< std::string >& strategies_ ) {

	for( int i = 0; i < 3; i++ ) {	

		strategies[ i ] = Factory::instance()->create( strategies_[ i ] );

		strategy_names[ i ] = strategies_[ i ];

		current_decisions[ i ] = 0;

		current_points[ i ] = 0;

		game_points[ i ] = 0;

	}

	current_step = 0;

}

Model::~Model() {

	if ( tournament != game_mode ) {

		for( int i = 0; i < 3; i++ ) {	

			delete strategies[ i ];

		}

	}
}

void Model::next() {

	bool decisions[ 3 ];

	for( int i = 0; i < 3; i++ ) {

		decisions[ i ] = strategies[ i ]->decision();

	}

	int index = 4 * decisions[ 0 ] + 2 * decisions[ 1 ] + decisions[ 2 ];	

	for( int i = 0; i < 3; i++ ) {

		current_decisions[ i ] = decisions[ i ];

		current_points[ i ] = matrix[ index ][ i ];

		game_points[ i ] += current_points[ i ];

		strategies[ i ]->save_decisions( decisions[ ( i + 1 ) % 3 ], decisions[ ( i + 2 ) % 3 ] );

	}

	current_step++;

}

const Game_mode& Model::get_game_mode() const {

	return game_mode;

}

const std::string* Model::get_strategy_names() const {

	return strategy_names;

}

const int& Model::get_current_step() const {

	return current_step;

}

const bool* Model::get_current_decisions() const {

	return current_decisions;

}

const int* Model::get_current_points() const {

	return current_points;

}

const int* Model::get_game_points() const {

	return game_points;

}

void Model::read_matrix( std::string& filename ) {

	std::ifstream file;

	file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );

	char ch;

	bool matrix_is_full = false;

	int current_number = 0;

	int input_matrix[ 24 ];

	int current_index = 0;

	try {

		file.open ( filename );

		while ( 1 ) {

			try {

				ch = file.get();

			} catch (...) {

				break;

			}

			if ( matrix_is_full ) {

				file.close();

				throw std::invalid_argument( "Invalid format of the matrix file\n" );

			}
						
			if ( ( ch >= '0' ) && ( ch <= '9' ) ) {

				if (  current_number > ( float ) ( INT_MAX - (  ch - '0' ) ) / 10 ) {

					file.close();

					throw std::invalid_argument( ( "Invalid format of the matrix file: \nthe " + std::to_string( current_index + 1 ) + " number of points in the matrix is too big, the maximal value is " + std::to_string( INT_MAX ) + "\n" ).data() );

				}

				current_number = current_number * 10 + ch - '0';

			} else if ( ( ch == ' ' ) || ( ch == '\n' ) ) {

				input_matrix[ current_index ] = current_number;

				current_number = 0;

				current_index++;

				if ( current_index == 24 ) {

					matrix_is_full = true;

				}

			} else {

				file.close();

				throw std::invalid_argument( ( "Ivalid format of the matrix file: \nthere is a wrong symbol in the " + std::to_string( current_index + 1 ) + " number of points: " + ch + "\n" ).data() );

			}

		}

		file.close();

		if ( !matrix_is_full ) {

			throw std::invalid_argument( "Invalid format of the matrix file\n" );

		}	

	} catch ( std::ifstream::failure e ) {

		throw e;

	}

	for( int i = 0; i < 8; i++ ) {

		for( int j = 0; j < 3; j++ ) {

			matrix[ i ][ j ] = input_matrix[ i * 3 + j ];

		}

	}

}