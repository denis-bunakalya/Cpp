#ifndef meta_h
#define meta_h

#include "strategy.h"

class Meta : public Strategy {

public:

	// Constructor
	Meta();

	// Returns the decision as a boolean value: true - cooperate, false - defect
	bool decision();	

	// Saves the decisions of the opponents
	void save_decisions( bool decision1, bool decision2 );

private:

	Strategy** strategies;

	int number_of_strategies;

	int current_strategy_number;

};

#endif