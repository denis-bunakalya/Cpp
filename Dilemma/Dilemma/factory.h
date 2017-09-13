#ifndef factory_h
#define factory_h

#include <string>
#include <map>

#include "strategy.h"

typedef Strategy* ( *creator_t )();

template< class Strategy_t>
static Strategy * creator() {

	return new Strategy_t;

}

class Factory {

public:

	Strategy* create( const std::string& name ) {

		if ( creators.end() == creators.find( name ) ) {

			return NULL;

		}		

		return creators[ name ]();

	}

	bool registerCreator( const std::string& name, creator_t creator ) {

		creators[ name ] = creator;

		return true;

	}

	static Factory* instance() {

		static Factory f;

		return &f;

	}

	const std::map< std::string, creator_t >& get_creators() const {

		return creators;

	}

	std::string get_list_of_available_strategies() const {

		std::string list = "";

		for( std::map< std::string, creator_t >::const_iterator it = creators.begin(); it != creators.end(); ++it ) {

			list += it->first + "\n\n";

		}

		return list;

	}


private:

	std::map< std::string, creator_t > creators;

};

#endif