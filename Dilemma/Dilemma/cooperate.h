#ifndef cooperate_h
#define cooperate_h

#include "strategy.h"

class Cooperate : public Strategy {

public:

	// Constructor
	Cooperate();

	// Returns the decision as a boolean value: true - cooperate, false - defect
	bool decision();	

	// Saves the decisions of the opponents
	void save_decisions( bool decision1, bool decision2 );

};

#endif