#include "factory.h"
#include "tit_for_tat.h"

namespace {

	bool b = Factory::instance()->registerCreator( "Tit_for_tat", creator< Tit_for_tat > );

}

Tit_for_tat::Tit_for_tat() : current_decision( true ) {}

bool Tit_for_tat::decision() {

	return current_decision;

}

void Tit_for_tat::save_decisions( bool decision1, bool decision2 ) {

	current_decision = decision1 && decision2;

}