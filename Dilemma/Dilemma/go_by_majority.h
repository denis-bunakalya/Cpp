#ifndef go_by_majority_h
#define go_by_majority_h

#include "strategy.h"

class Go_by_majority : public Strategy {

public:

	// Constructor
	Go_by_majority();

	// Returns the decision as a boolean value: true - cooperate, false - defect
	bool decision();	

	// Saves the decisions of the opponents
	void save_decisions( bool decision1, bool decision2 );

private:

	int cooperate;

	int defect;

};

#endif