#ifndef strategy_h
#define strategy_h

class Strategy {

public:

	// Returns the decision as a boolean value: true - cooperate, false - defect
	virtual bool decision() = 0;

	// Saves the decisions of the opponents
	virtual void save_decisions( bool decision1, bool decision2 ) = 0;

	// Destructor
	virtual ~Strategy() {}

};

#endif