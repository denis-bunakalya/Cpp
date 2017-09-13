#ifndef alternate_h
#define alternate_h

#include "strategy.h"

class Alternate : public Strategy {

public:

	// Constructor
	Alternate();

	// Returns the decision as a boolean value: true - cooperate, false - defect
	bool decision();	

	// Saves the decisions of the opponents
	void save_decisions( bool decision1, bool decision2 );

private:

	bool current_decision;

};

#endif