#ifndef controller_h
#define controller_h

#include "model.h"
#include "view.h"

class Controller {

public:

	// Constructor
	Controller( int argc, char** argv );

	// Destructor
	~Controller();

	// Reads the number of steps from the string "input_string" and
	// saves it over the integer pointer "steps".
	// Returns true if the operation was successful
	static bool read_number_of_steps( std::string input_string, int* steps );

private:

	Model* model;

	View view;			

	// Starts the game
	void play();

	// Reads the number of steps from the string "input_string" and calculates them
	// Calculates one step if the string "input_string" is empty
	void tick( std::string input_string );		

	// Calculates the "number_of_steps" steps
	void do_steps( int number_of_steps );

};

#endif