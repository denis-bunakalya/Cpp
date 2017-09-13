#include <iostream>
#include <string>

#include "view.h"
#include "field.h"

using namespace std;

View::View() {}

void View::print( string print_string ) {

	cout << print_string;

}

void View::help() {

	cout << "Help contents:" << endl;	

	cout << "dump <filename> - save the universe to a file" << endl;

	cout << "tick <n> - calculate n (by default 1) steps and show the result" << endl;

	cout << "exit - end the game" << endl;

	cout << "help - show help contents" << endl;

}

void View::show_launch_modes_help_and_exit() {

	cout << endl;

	cout << "Launch modes: " << endl << endl;

	cout << "no parameters - launch an example" << endl << endl;

	cout << "1 parameter: <filename> - read the universe from the file" << endl << endl;

	cout << "3 parameters: <input filename> -i <number of iterations> -o <output filename> -" << endl;

	cout << " - read the universe from the input file, calculate the specified number of iterations and save the result to the output file" << endl << endl;

	throw exception();

}

void View::print_examples() {

	cout << "Please choose one of the following examples:" << endl << endl;

	cout << "1 - Glider" << endl << endl;

	cout << "2 - Sierpinski triangle" << endl << endl;

	cout << "3 - Empty54" << endl << endl;

	cout << "4 - R-Pentomino" << endl << endl;

	cout << "5 - H-Copy" << endl << endl;

	cout << "6 - Replicator in HighLife" << endl << endl;

	cout << "7 - Exploding in Seeds" << endl << endl;

	cout << "8 - Move" << endl << endl;

	cout << "9 - Swimmer and sailor" << endl  << endl;

	cout << "10 - Medusa" << endl;

}

void View::print_universe( const string& universeName, const bool* birth, const bool* survival, 
						  
						  const int& currentIterationNumber, const int& width, const int& height, const Field* field ) {

	cout << universeName << " ";

	cout << rulesToString( birth, survival ) << " ";

	cout << "iteration: " << currentIterationNumber << "\n\n";

	cout << string( "" ).append( width + 2, '-' ) << "\n";

	for( int i = 0; i < height; i++ ) {		

		cout << "|";

		for( int j = 0; j < width; j++ ) {			

			cout << ( ( field->get_cells()[ i ][ j ] ) ? "*" : " " ) ;			

		}

		cout << "|";

		cout << "\n";

	}

	cout << string ( "" ).append( width + 2, '-' ) << "\n";

	cout << "\n";

}

string View::rulesToString( const bool* birth, const bool* survival ) {

	string rules = "B";

	for( int i = 0; i < 9; i++ ) {

		if ( birth[i] ) {		

			rules += '0' + i;

		}

	}

	rules += "/S";

	for( int i = 0; i < 9; i++ ) {

		if ( survival[i] ) {		

			rules += '0' + i;

		}

	}	

	return rules;

}