#ifndef tit_for_tat_h
#define tit_for_tat_h

#include "strategy.h"

class Tit_for_tat : public Strategy {

public:

	// Constructor
	Tit_for_tat();

	// Returns the decision as a boolean value: true - cooperate, false - defect
	bool decision();	

	// Saves the decisions of the opponents
	void save_decisions( bool decision1, bool decision2 );

private:

	bool current_decision;

};

#endif