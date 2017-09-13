#include <iostream>

#include "view.h"
#include "factory.h"

View::View() {}

void View::print( std::string print_string ) {

	std::cout << print_string;

}

void View::help() {

	std::cout << "Help contents:" << std::endl;	

	std::cout << "tick <n> - calculate n (by default 1) steps and show the result" << std::endl;

	std::cout << "quit - end the game" << std::endl;

	std::cout << "help - show help contents" << std::endl;

}

void View::show_launch_modes_help_and_exit() {

	std::cout << std::endl;

	std::cout << "Usage: " << std::endl << std::endl;

	std::cout << "strategy_name_1 strategy_name_2 strategy_name_3 ... - " << std::endl << std::endl;

	std::cout << "        the names of the strategies, that should be used in the game" << std::endl;

	std::cout << "        (more than three strategies - only for the tournament mode)" << std::endl << std::endl;

	std::cout << "-mode=[detailed|fast|tournament] - " << std::endl << std::endl;

	std::cout << "        (optional) the game mode (by default detailed)" << std::endl << std::endl;

	std::cout << "-steps=<n> - " << std::endl << std::endl;

	std::cout << "        (optional but only and necessarily for the tournament mode) " << std::endl;

	std::cout << "        the number of steps for simulation" << std::endl << std::endl;

	std::cout << "-matrix=<filename> - " << std::endl << std::endl;

	std::cout << "        (optional) the name of the file with the matrix for the game" << std::endl << std::endl;

	std::cout << "Available strategies:" << std::endl << std::endl;

	std::cout << Factory::instance()->get_list_of_available_strategies();

	std::cout << std::endl;

	throw std::exception();

}

void View::print_model( const std::string* strategy_names, const int& current_step,

		const bool* current_decisions, const int* current_points, const int* game_points ) {			

	std::cout << std::string( strategy_names[ 0 ].length() + strategy_names[ 1 ].length() + strategy_names[ 2 ].length() + 2, '-' ) << "\n";

	std::cout << "step: " << current_step << "\n\n";

	for( int i = 0; i < 3; i++ ) {

		std::cout << strategy_names[ i ] + " ";		

	}

	std::cout << "\n\n";

	int distance;

	if ( 0 != current_step ) {

		for( int i = 0; i < 3; i++ ) {

			distance = strategy_names[ i ].length() / 2;

			std::cout << std::string( distance, ' ' );

			std::cout << ( current_decisions[ i ] ? "C" : "D" );

			std::cout << std::string( strategy_names[ i ].length() - distance, ' ' );

		}

		std::cout << "\n\n";

		for( int i = 0; i < 3; i++ ) {

			distance = strategy_names[ i ].length() / 2;

			std::cout << std::string( distance, ' ' );

			std::cout << current_points[ i ];

			std::cout << std::string( strategy_names[ i ].length() - distance, ' ' );

		}

		std::cout << "\n\n";

	}

	for( int i = 0; i < 3; i++ ) {

		distance = ( strategy_names[ i ].length() - std::to_string( game_points[ i ] ).length() + 1 ) / 2;

		std::cout << std::string( distance, ' ' );

		std::cout << game_points[ i ];

		std::cout << std::string( strategy_names[ i ].length() - ( distance + std::to_string( game_points[ i ] ).length() ) + 1, ' ' );

	}

	std::cout << "\n";

	std::cout << std::string( strategy_names[ 0 ].length() + strategy_names[ 1 ].length() + strategy_names[ 2 ].length() + 2, '-' );

	std::cout << "\n";

}

void View::print_for_tournament(const std::string* strategy_names, const int* game_points ) {

	std::cout << std::string( strategy_names[ 0 ].length() + strategy_names[ 1 ].length() + strategy_names[ 2 ].length() + 2, '-' ) << "\n";	

	for( int i = 0; i < 3; i++ ) {

		std::cout << strategy_names[ i ] + " ";		

	}

	std::cout << "\n\n";

	int distance;

	for( int i = 0; i < 3; i++ ) {

		distance = ( strategy_names[ i ].length() - std::to_string( game_points[ i ] ).length() + 1 ) / 2;

		std::cout << std::string( distance, ' ' );

		std::cout << game_points[ i ];

		std::cout << std::string( strategy_names[ i ].length() - ( distance + std::to_string( game_points[ i ] ).length() ) + 1, ' ' );

	}

	std::cout << "\n";

	std::cout << std::string( strategy_names[ 0 ].length() + strategy_names[ 1 ].length() + strategy_names[ 2 ].length() + 2, '-' );

	std::cout << "\n";

}
	
void View::print_tournament_results( const std::multimap< int, std::string >& sorted_strategies ) {

	std::cout << "\n" << "Tournament results:" << "\n\n";

	std::multimap< int, std::string >::const_iterator it;

	for( it = sorted_strategies.begin(); it != sorted_strategies.end(); it++ ) {

		std::cout << it->first << " - " << it->second << "\n\n";

	}

}