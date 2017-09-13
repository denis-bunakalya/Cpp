#include "factory.h"
#include "cooperate.h"

namespace {

	bool b = Factory::instance()->registerCreator( "Cooperate", creator< Cooperate > );

}

Cooperate::Cooperate() {}

bool Cooperate::decision() {

	return true;

}

void Cooperate::save_decisions( bool decision1, bool decision2 ) {}