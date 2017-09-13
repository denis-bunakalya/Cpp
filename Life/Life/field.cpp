#include "field.h"

using namespace std;

Field::Field( vector< vector < bool > >& cells_ ) {

	cells = cells_;

}

const vector< vector < bool > >& Field::get_cells() const {

	return cells;

}

void Field::set_cells( vector< vector < bool > >& cells_ ) {

	cells = cells_;

}