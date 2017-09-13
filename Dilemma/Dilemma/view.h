#ifndef view_h
#define view_h

#include <map>

class View {

public:

	// Constructor
	View();

	// Prints the string "print_string"
	static void print( std::string print_string );

	// Shows the help contents
	void help();
	
	// Shows the help for the launch modes
	void show_launch_modes_help_and_exit();

	// Prints the model members
	void print_model( const std::string* strategy_names, const int& current_step,

	const bool* current_decisions, const int* current_points, const int* game_points );

	// Prints the results of one competition for the tournament
	void print_for_tournament( const std::string* strategy_names, const int* game_points );

	// Prints the results of the tournament
	void print_tournament_results( const std::multimap< int, std::string >& sorted_strategies );

};

#endif