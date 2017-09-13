#include <iostream>
#include <string>
#include <map>

#include "tournament.h"
#include "model.h"
#include "view.h"

Tournament::Tournament( std::vector< std::string > strategies, int steps ) {

	View view;

	std::vector< int > total_points;	

	total_points.resize( strategies.size() );

	fill( total_points.begin(), total_points.end(), 0 );

	std::vector< std::string > current_strategies;

	current_strategies.resize( 3 );

	for( int i = 0; i < strategies.size() - 2; i++ ) {

		for( int j = i + 1; j < strategies.size() - 1; j++ ) {

			for( int k = j + 1; k < strategies.size(); k++ ) {

				current_strategies[ 0 ] = strategies[ i ];

				current_strategies[ 1 ] = strategies[ j ];

				current_strategies[ 2 ] = strategies[ k ];

				Model model( current_strategies );

				for( int m = 0; m < steps; m++ ) {

					model.next();

				}

				view.print_for_tournament( model.get_strategy_names(), model.get_game_points() );

				total_points[ i ] += model.get_game_points()[ 0 ];

				total_points[ j ] += model.get_game_points()[ 1 ];

				total_points[ k ] += model.get_game_points()[ 2 ];

			}

		}

	}

	std::multimap< int, std::string > sorted_strategies;

	for( int k = 0; k < strategies.size(); k++ ) {

		sorted_strategies.insert( std::pair< int, std::string>( total_points[ k ], strategies[ k ] ) );

	}

	view.print_tournament_results( sorted_strategies );

}