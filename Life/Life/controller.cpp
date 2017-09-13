#include <iostream>
#include <string>

#include "controller.h"

using namespace std;

Controller::Controller( int argc, char** argv ) { 

	string example_string;

	if ( 1 == argc ) {

		view.print_examples();

		string inputString;	

		while( true ) {		

			view.print( "\n" );

			getline( cin, inputString );		

			if ( "1" == inputString ) {			

				example_string= "#Life 1.06\n#N Glider\n#R B3/S23\n#S 40 18\n0 -1\n1 0\n-1 1\n0 1\n1 1";

				break;

			} else if ( "2" == inputString ) {	

				example_string= "#Life 1.06\n#N Sierpinski triangle\n#R B1/S12\n#S 61 49\n0 0";

				break;

			} else if ( "3" == inputString ) {	

				example_string= "#Life 1.06\n#N Empty54\n#R B3/S23\n#S 61 49\n0 0\n0 1\n0 2\n1 0\n1 2\n2 0\n2 2\n4 0\n4 2\n5 0\n5 2\n6 0\n6 1\n6 2";

				break;

			} else if ( "4" == inputString ) {	

				example_string= "#Life 1.06\n#N R-Pentomino\n#R B3/S23\n#S 61 49\n1 0\n2 0\n0 1\n1 1\n1 2";

				break;

			} else if ( "5" == inputString ) {	

				example_string= "#Life 1.06\n#N H-Copy\n#R B1357/S1357\n#S 61 49\n0 0\n2 0\n0 1\n1 1\n2 1\n0 2\n2 2";

				break;

			} else if ( "6" == inputString ) {	

				example_string= "#Life 1.06\n#N Replicator in HighLife\n#R B36/S23\n#S 61 49\n0 0\n1 0\n2 0\n-1 1\n2 1\n-2 2\n2 2\n-2 3\n1 3\n-2 4\n-1 4\n0 4";

				break;

			} else if ( "7" == inputString ) {	

				example_string= "#Life 1.06\n#N Exploding in Seeds\n#R B2/S\n#S 61 49\n0 0\n2 1\n-1 2\n1 2\n3 2\n-1 3\n0 3\n3 3\n3 4\n4 4\n0 5\n1 5\n2 5\n2 6";

				break;

			} else if ( "8" == inputString ) {	

				example_string= "#Life 1.06\n#N Move\n#R B245/S368\n#S 61 49\n0 0\n0 1\n0 2\n0 3\n1 0\n1 1\n1 2\n1 3";

				break;

			} else if ( "9" == inputString ) {	

				example_string= "#Life 1.06\n#N Swimmer and sailor\n#R B3/S35\n#S 30 30\n0 0\n1 0\n2 0\n2 1\n3 1\n0 2\n1 2\n2 2\n1 7\n2 7\n2 8\n3 8\n0 9\n1 9\n2 9";

				break;

			} else if ( "10" == inputString ) {	

				example_string= "#Life 1.06\n#N Medusa\n#R B3/S245\n#S 30 30\n0 0\n0 1\n1 1\n0 2\n1 2\n2 2";

				break;

			} else {

				view.print( "Invalid input. Please enter the number of an example: \n" );

			}

		}

		view.print( "\n" );

	}

	try {

	universe = new Universe( argc, argv, example_string );	

	} catch ( Launch_mode_exception launch_mode_exception ) {

		view.show_launch_modes_help_and_exit();

	} catch ( exception exc ) {

		view.print( exc.what() );

		throw exception();

	}

	view.print( universe->get_warnings() );

	if ( 6 == argc ) {

		int numberOfIterations;

		if ( read_number_of_iterations( argv[3], &numberOfIterations ) ) {

			for( int i =0; i < numberOfIterations; i++ ) {

				universe->next();

			}

		} else {

			view.show_launch_modes_help_and_exit();

		}		

		universe->dump( argv[5] );		

		view.print( "the universe was successfully calculated and saved \n" );

		throw exception();

	}

	
	view.print( universe->get_warnings() );

	view.print_universe( universe->get_universe_name(), universe->get_birth(), universe->get_survival(), 

		universe->get_current_iteration_number(), universe->get_width(), universe->get_height(), universe->get_field() );

	view.help();

	play();

}

Controller::~Controller() {

	delete universe;

}

void Controller::play() {

	string inputString;	

	while( true ) {		

		view.print( "\n" );

		getline( cin, inputString );	

		view.print( "\n" );

		if ( "tick" == inputString.substr( 0, 4 ) ) {

			tick( inputString.substr( 4, inputString.length() - 4 ) );

		} else if ( "t" == inputString.substr( 0 , 1 ) ) {

			tick( inputString.substr( 1, inputString.length() - 1 ) );

		} else if ( "dump " == inputString.substr( 0, 5 ) ) {

			try {
				
			universe->dump( inputString.substr( 5, inputString.length() - 5 ) );  
			
			view.print( "the universe was successfully saved \n" );	

			} catch ( exception exc ) {

				view.print( exc.what() );

			}				

		} else if ( "exit" == inputString ) {

			break;

		} else {

			view.help();

		}

	}

}

void Controller::tick( string inputString ) {

	if ( 0 == inputString.length() ) {

		universe->next();		

	} else {

		if ( ' ' != inputString[0] ) {

			view.help();

			return;

		}

		int numberOfIterations;

		if ( read_number_of_iterations( inputString.substr( 1, inputString.length() - 1 ), &numberOfIterations ) ) {

			for( int i = 0; i < numberOfIterations; i++ ) {

				universe->next();

			}

		} else {

			view.help();

			return;

		}

	}

	view.print_universe( universe->get_universe_name(), universe->get_birth(), universe->get_survival(), 

		universe->get_current_iteration_number(), universe->get_width(), universe->get_height(), universe->get_field() );

}

bool Controller::read_number_of_iterations( string inputString, int* numberOfIterations ) {

	*numberOfIterations = 0;

	for( int i = 0; i < inputString.length(); i++ ) {

		if ( ( inputString.at( i ) < '0' ) || ( inputString.at( i ) > '9' ) ) {

			view.print( "Ivalid input format: there is a wrong symbol in the number of iterations: " 

				+ inputString.substr( i, 1 ) + "\n" );			

			return false;

		}			

		if (  *numberOfIterations > ( float ) ( INT_MAX - ( inputString.at ( i ) - '0' ) ) / 10 ) {

			view.print( "Invalid input format: the number of iterations is too big, the maximal value is " 

				+ to_string( INT_MAX ) + "\n" );			

			return false;

		}

		*numberOfIterations = *numberOfIterations * 10 + inputString.at ( i ) - '0';

	}	

	return true;

}
