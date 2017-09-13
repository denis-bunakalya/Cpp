#include "factory.h"
#include "go_by_majority.h"

namespace {

	bool b = Factory::instance()->registerCreator( "Go_by_majority", creator< Go_by_majority > );

}

Go_by_majority::Go_by_majority() : cooperate( false ), defect( false ) {}

bool Go_by_majority::decision() {

	return ( cooperate >= defect );

}

void Go_by_majority::save_decisions( bool decision1, bool decision2 ) {

	cooperate += decision1 + decision2;

	defect += !decision1 + !decision2;

}