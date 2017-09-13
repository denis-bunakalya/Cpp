#ifndef defect_h
#define defect_h

#include "strategy.h"

class Defect : public Strategy {

public:

	// Constructor
	Defect();

	// Returns the decision as a boolean value: true - cooperate, false - defect
	bool decision();	

	// Saves the decisions of the opponents
	void save_decisions( bool decision1, bool decision2 );

};

#endif