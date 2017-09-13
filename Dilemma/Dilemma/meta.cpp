#include "factory.h"
#include "meta.h"

namespace {

	bool b = Factory::instance()->registerCreator( "Meta", creator< Meta > );

}

Meta::Meta() : current_strategy_number( 0 ) {

	std::map< std::string, creator_t > creators = Factory::instance()->get_creators();

	number_of_strategies = creators.size() - 1;	

	strategies = new Strategy*[ number_of_strategies ];

	int i = 0;

	for( std::map< std::string, creator_t >::const_iterator it = creators.begin(); it != creators.end(); ++it ) {

		if( it->first != "Meta" ) {

		strategies[ i ] = it->second();

		i++;

		}

	}

}

bool Meta::decision() {

	return strategies[ current_strategy_number ]->decision();

}

void Meta::save_decisions( bool decision1, bool decision2 ) {

	strategies[ current_strategy_number ]->save_decisions( decision1, decision2 );

	current_strategy_number = ( current_strategy_number + 1 ) % number_of_strategies;

}