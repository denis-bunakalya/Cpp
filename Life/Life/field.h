#ifndef field_h
#define field_h

#include <vector>

class Field {

public:

	// Constructor
	Field( std::vector< std::vector < bool > >& cells_ );

	// Returns the cells of the field
	const std::vector< std::vector < bool > >& get_cells() const;

	// Sets the cells of the filed to the values in "cells_"
	void set_cells( std::vector< std::vector < bool > >& cells_ );

private:
	
	std::vector< std::vector < bool > > cells;

};

#endif