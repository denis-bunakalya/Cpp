#ifndef controller_h
#define controller_h

#include "universe.h"
#include "view.h"

class Controller {

public:

	// Constructor
	Controller( int argc, char** argv );

	// Destructor
	~Controller();

private:

	Universe* universe;

	View view;	

	// Starts the game
	void play();

	// Reads the number of iterations from the string "inputString" and calculates them.
	// Calculates one iteration if the string "inputString" is empty
	void tick( std::string inputString );		
	
	// Reads the number of iterations from the string "inputString" and saves it over the integer pointer "numberOfIterations"
	bool read_number_of_iterations( std::string inputString, int* numberOfIterations );

};

#endif

