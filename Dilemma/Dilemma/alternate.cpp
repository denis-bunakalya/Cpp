#include "factory.h"
#include "alternate.h"

namespace {

	bool b = Factory::instance()->registerCreator( "Alternate", creator< Alternate > );

}

Alternate::Alternate() : current_decision( false ) {}

bool Alternate::decision() {

	current_decision = !current_decision;

	return current_decision;

}

void Alternate::save_decisions( bool decision1, bool decision2 ) {}