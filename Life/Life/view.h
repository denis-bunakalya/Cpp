#ifndef view_h
#define view_h

#include "field.h"

class View {

public:

	View();

	// Prints the string "print_string"
	void print( std::string print_string );

	// Shows the help contents
	void help();

	// Shows the help for the launch modes
	void show_launch_modes_help_and_exit();

	// Prints the model members
	void print_universe( const std::string& universeName, const bool* birth, const bool* survival, 

						 const int& currentIterationNumber, const int& width, const int& height, const Field* field );

	// Returns the string with the birth and survival rules from the boolean arrays "birth" and "survival"
	std::string rulesToString( const bool* birth, const bool* survival );

	// Prints the request to choose one of the examples with the names and numbers of them
	void print_examples();

};

#endif