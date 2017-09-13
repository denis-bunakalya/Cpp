#include "factory.h"
#include "defect.h"

namespace {

	bool b = Factory::instance()->registerCreator( "Defect", creator< Defect > );

}

Defect::Defect() {}

bool Defect::decision() {

	return false;

}

void Defect::save_decisions( bool decision1, bool decision2 ) {}