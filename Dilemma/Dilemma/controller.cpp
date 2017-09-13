#include <iostream>
#include <string>
#include <fstream>

#include "controller.h"

Controller::Controller(int argc, char** argv) { 

	try {

	model = new Model( argc, argv );

	} catch ( std::ifstream::failure e ) {

		view.print( "Exception opening/reading/closing matrix file\n" );

		view.show_launch_modes_help_and_exit();

	} catch ( std::invalid_argument exc ) {

		view.print( exc.what() );

		view.show_launch_modes_help_and_exit();

	} catch ( std::exception exc ) {

		view.show_launch_modes_help_and_exit();

	}

	if ( tournament != model->get_game_mode() ) {

		view.print_model( model->get_strategy_names(), model->get_current_step(),

			model->get_current_decisions(), model->get_current_points(), model->get_game_points());

		view.help();

		play();	

	}

}

Controller::~Controller() {

	delete model;

}

void Controller::play() {

	std::string input_string;	

	while( true ) {		

		view.print( "\n" );

		getline( std::cin, input_string );	

		view.print( "\n" );

		if ( "tick" == input_string.substr( 0, 4 ) ) {

			tick( input_string.substr( 4, input_string.length() - 4 ) );

		} else if ( "quit" == input_string ) {

			break;

		} else {

			view.help();

		}

	}

}

void Controller::tick( std::string  input_string ) {

	if ( 0 ==  input_string.length() ) {

		model->next();		

		view.print_model( model->get_strategy_names(), model->get_current_step(),

			model->get_current_decisions(), model->get_current_points(), model->get_game_points());

	} else {

		if ( ' ' !=  input_string[0] ) {

			view.help();

			return;

		}

		int number_of_steps = 0;

		if ( !read_number_of_steps(  input_string.substr( 1,  input_string.length() - 1 ), &number_of_steps ) ) {

			view.help();

			return;

		}

		do_steps( number_of_steps );

	}	

}

void Controller::do_steps( int number_of_steps ) {

	for( int i = 0; i < number_of_steps; i++ ) {

		model->next();

		if ( detailed == model->get_game_mode() ) {

			view.print_model( model->get_strategy_names(), model->get_current_step(),

				model->get_current_decisions(), model->get_current_points(), model->get_game_points());

		}

	}

	if ( fast == model->get_game_mode() ) {

		view.print_model( model->get_strategy_names(), model->get_current_step(),

		model->get_current_decisions(), model->get_current_points(), model->get_game_points());

	}

}

bool Controller::read_number_of_steps( std::string input_string, int* steps ) {

	for( int i = 0; i <  input_string.length(); i++ ) {

		if ( (  input_string.at( i ) < '0' ) || (  input_string.at( i ) > '9' ) ) {

			View::print( std::string( "Ivalid input format: \nthere is a wrong symbol in the number of steps: " ) + input_string.at( i ) + std::string( "\n" ) );			

			return false;

		}			

		if (  *steps > ( float ) ( INT_MAX - (  input_string.at ( i ) - '0' ) ) / 10 ) {

			View::print( std::string( "Invalid input format: \nthe number of steps is too big, the maximal value is " ) + std::to_string( INT_MAX ) + std::string( "\n" ) );			

			return false;

		}

		*steps = *steps * 10 +  input_string.at ( i ) - '0';

	}

	return true;

}

