#ifndef universe_h
#define universe_h

#include "field.h"

class Universe {

public:

	// Constructor
	Universe( int argc, char** argv, std::string example_string );

	// Destructor
	~Universe();

	// Calculates the next state of the universe
	void next();

	// Saves the universe to a file with the name specified in the string "inputString".
	// Returns true if the saving was successful
	void dump( std::string inputString ) const;

	// Returns the name of the universe
	const std::string& get_universe_name() const;

	// Returns the field of the universe
	const Field* get_field() const;

	// Returns the width of the universe
	const int& get_width() const;

	// Returns the height of the universe
	const int& get_height() const;

	// Returns the birth rules of the universe
	const bool* get_birth() const;

	// Returns the survival rules of the universe
	const bool* get_survival() const;

	// Returns the current iteration number of the universe
	const int& get_current_iteration_number() const;

	// Returns a string with the occured warnings
	const std::string& get_warnings() const;

	// Constructor for tests
	Universe( std::string constructor_for_tests, std::string universeName, int width_, int height_, 
		
		std::vector< std::vector < bool > > cells_, bool birth_[ 9 ], bool survival_[ 9 ] );

private:	

	std::string universeName;	

	Field* field;

	int width;

	int height;

	bool birth[9];

	bool survival[9];

	int currentIterationNumber;

	std::vector< std::vector < bool > > cellsTemp;

	std::string warnings;

	// Calculates the next state of the cell with the coordinates i and j
	void next( int i, int j );

	// Returns the number of neighbours of the cell with the coordinates i and j
	int neighbours( int i, int j ) const;

	// Returns the transition rules in a string
	std::string rulesToString() const;

	// Returns a string with the content of the file with the name specified over the char pointer "filename"
	std::string readInputFile( char* filename ) const;

	// Creates a field from the string "s"
	// Uses the string "fileName" as the universe name, if it's not specified in the string "s"
	void parse_string_and_create_universe( std::string s, std::string fileName );

	// Reads the transition rules from the string "s" and
	// saves them into the boolean arrays over the pointers "birth" and "survival"
	void readRules( std::string s, bool ( *birth )[ 9 ], bool ( *survival )[ 9 ] );	

	// Reads the field size from the string "s" and saves it into the integers over the pointers "width" and "height"
	void readSize( std::string s, int* width, int* height ) const;

	// Reads the coordinates of a cell from the string "s" and 
	// sets the element with these coordinates in the two-dimensional boolean vector "cells" on true.
	// Uses the integer "cellNumber" for displaying the number of the cell, 
	// if an error occurred by reading the coordinates of it
	void readCoordinate( std::string s, std::vector< std::vector < bool > >* cells, int cellNumber );		

	// Creates the universe using the universe name, the width and height, 
	// the cells of the field and the birth and survival rules
	void create_universe( std::string universeName, int width_, int height_, std::vector< std::vector < bool > > cells_, 
		
		bool birth_[ 9 ], bool survival_[ 9 ] );

	// Throws an exception with the messages of all warnings an of the string "s"
	void throw_exception_with_warnings( std::string s ) const;

};

class Launch_mode_exception : public std::exception {};

#endif