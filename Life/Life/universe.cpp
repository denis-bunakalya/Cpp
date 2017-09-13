#include <iostream>
#include <fstream>
#include <string>

#include "universe.h"

using namespace std;

Universe::Universe( int argc, char** argv, string example_string ) {	

	string s;

	string filename;

	if ( 1 == argc ) {

		s = example_string;

	} else if ( 2 == argc ) {

		s = readInputFile( argv[1] );

		filename = argv[1];

	} else if ( 6 == argc ) {		

		if ( ( string( "-i" ).compare( argv[2] ) ) || ( string( "-o" ).compare( argv[4] ) ) ) {

			throw Launch_mode_exception();

		}

		s = readInputFile( argv[1] );

		filename = argv[5];		

	} else {

		throw Launch_mode_exception();

	}	

	parse_string_and_create_universe( s, filename );

}

void Universe::create_universe( string universeName_, int width_, int height_, vector< vector < bool > > cells_, 

							   bool birth_[ 9 ], bool survival_[ 9 ] ) {

	universeName = universeName_;

	width = width_;

	height = height_;

	field = new Field( cells_ );

	currentIterationNumber = 0;

	cellsTemp.resize( height );

	copy( birth_, birth_ + 9, birth );

	copy( survival_, survival_ + 9, survival );

	for( int i = 0; i < height; i++ ) {

		cellsTemp[ i ].resize( width );

	}

}

Universe::~Universe() {

	delete field;

}

void Universe::next() {	

	for( int i = 0; i < height; i++ ) {

		for( int j = 0; j < width; j++ ) {

			next( i, j );

		}

	}

	field->set_cells( cellsTemp );

	currentIterationNumber++;

}

void Universe::next( int i, int j ) {

	int n = neighbours( i, j );

	if ( !field->get_cells()[ i ][ j ] ) {

		cellsTemp[ i ][ j ] = birth[ n ];

		return;

	}

	cellsTemp[ i ][ j ] = survival[ n ];

}

int Universe::neighbours( int i, int j ) const {

	int neighbours = 0;

	int right = ( j + 1 ) % width;

	int left = ( j == 0 ) ? ( width - 1 ) : ( j - 1 );

	int up = ( i == 0 ) ? ( height - 1 ) : ( i - 1 );

	int down = ( i + 1 ) % height;


	if ( field->get_cells()[ up ][ left ] ) neighbours++;

	if ( field->get_cells()[ up ][ j ] ) neighbours++;

	if ( field->get_cells()[ up ][ right ] ) neighbours++;

	if ( field->get_cells()[ i ][ right ] ) neighbours++;

	if ( field->get_cells()[ down ][ right ] ) neighbours++;

	if ( field->get_cells()[ down ][ j ] ) neighbours++;

	if ( field->get_cells()[ down ][ left ] ) neighbours++;

	if ( field->get_cells()[ i ][ left ] ) neighbours++;


	return neighbours;

}

string Universe::rulesToString() const {

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

const string& Universe::get_universe_name() const {

	return universeName;

}

const Field* Universe::get_field() const {

	return field;

}

const int& Universe::get_width() const {

	return width;

}

const int& Universe::get_height() const {

	return height;

}

const bool* Universe::get_birth() const {

	return birth;

}

const bool* Universe::get_survival() const {

	return survival;

}

const int& Universe::get_current_iteration_number() const {

	return currentIterationNumber;

}

const string& Universe::get_warnings() const {

	return warnings;

}

string Universe::readInputFile( char* filename ) const {

	ifstream input ( filename );		

	if ( !input ) {

		throw exception( string( "can not open the input file: " + string( filename ) + "\n" + 
			
			"please check the input correctness of the path and file name \n" ).data() );			

	}		

	string s;

	char ch;

	while ( input.get( ch ) ) s += ch;		

	input.close();

	return s;

}

void Universe::parse_string_and_create_universe( string s, string fileName ) { 	

	if ( 0 != s.substr( 0, 11 ).compare( "#Life 1.06\n" ) ) {

		throw exception( "Ivalid file format: it is not Life 1.06 format \n" );
		
	}

	int i = 11; 

	int j = 0;




	string universeName;

	if ( 0 == s.substr( 11, 3 ).compare( "#N " ) ) {		

		i = s.find( '\n', 15);

		if ( i == -1 ) {

			throw exception( "Ivalid file format: there are no new lines after the universe name, each format point must be in a new line \n" );
			
		}

		universeName = s.substr( 14, i - 14 ); 

		i++;

	}

	else {

		warnings += "Warning: there is no universe name \n";

		universeName = fileName;

	}




	bool birth[ 9 ] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	bool survival[ 9 ] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	j = s.find( '\n', i + 4 );

	if ( 0 == s.substr( i , 4 ).compare( "#R B" ) ) {		

		if ( -1 == j ) {

			throw_exception_with_warnings( "Ivalid file format: there are no new lines after the transition rules, each format point must be in a new line \n" );
			
		}

		readRules( s.substr( i + 4, j - i - 4 ), &birth, &survival );

		i = j + 1;

	}

	else {

		warnings += "Warning: there are no transition rules \n";		

		birth[ 3 ] = 1;

		survival[ 2 ] = 1;

		survival[ 3 ] = 1;		

	}




	if ( 0 != s.substr( i, 3 ).compare( "#S " ) ) {

		throw_exception_with_warnings( "Ivalid file format: there is no universe size \n" );
		
	}

	i = i + 3;

	j = s.find( '\n', i );

	if ( j == -1 ) {

		throw_exception_with_warnings( "Ivalid file format: there are no new lines after the universe size, each format point must be in a new line \n" );
		
	}

	int width;

	int height;

	readSize( s.substr( i, j - i ), &width, &height );




	vector< vector < bool > > cells;

	cells.resize( height );

	for( int k = 0; k < height; k++ ) {

		cells[ k ].resize( width );

		fill( cells[ k ].begin(), cells[ k ].end(), 0 );		

	}

	int cellNumber = 1;

	i = j + 1;

	bool notEnd = true;

	while ( notEnd ) {

		j = s.find( '\n', i );

		if ( ( j == -1 ) || ( j == s.size() - 1 ) ) {

			if ( -1 == j ) {

				j = s.size();

			}

			notEnd = false;

		}

		readCoordinate( s.substr( i, j - i ), &cells, cellNumber );

		cellNumber++;

		i = j + 1;		

	}




	create_universe( universeName, width, height, cells, birth, survival );

}

void Universe::readRules( string s, bool ( *birth )[ 9 ], bool ( *survival )[ 9 ] ) {

	int slashPosition = s.find( "/S" ); 

	if ( -1 == slashPosition ) {

		throw_exception_with_warnings( "Ivalid file format: there is no \"/S\" in the transition rules " );

	}


	for( int i = 0; i < slashPosition; i++) {

		if ( ( s.at( i ) < '0' ) || ( s.at( i ) > '8' ) ) {

			throw_exception_with_warnings( string( "Ivalid file format: there is a wrong symbol in the birth rules: "

				+ to_string( s.at( i ) ) + "\n" ).data() );

		}

		if ( ( *birth )[ s.at ( i ) - '0' ] ) {

			warnings += "Warning: there is a repeating birth rule: " + to_string( s.at( i ) ) + "\n";	

		}

		( *birth )[ s.at ( i ) - '0' ] = 1;

	}


	for( int i = slashPosition + 2; i < s.length(); i++ ) {

		if ( ( s.at( i ) < '0' ) || ( s.at( i ) > '8' ) ) {

			throw_exception_with_warnings( string( "Ivalid file format: there is a wrong symbol in the survival rules: " 

				+ to_string (s.at( i ) ) + "\n" ).data() );

		}

		if ( ( *survival )[ s.at ( i ) - '0' ] ) {

			warnings += "Warning: there is a repeating survival rule: " + to_string( s.at( i ) ) + "\n";	

		}

		( *survival )[ s.at ( i ) - '0' ] = 1;

	}

}

void Universe::readSize( string s, int* width, int* height ) const {

	int spacePosition = s.find( " " ); 

	if ( -1 == spacePosition ) {

		throw_exception_with_warnings( "Ivalid file format: there is no space symbol in the universe size \n" );

	}


	*width = 0;	

	for( int i = 0; i < spacePosition; i++ ) {

		if ( ( s.at( i ) < '0' ) || ( s.at( i ) > '9' ) ) {

			throw_exception_with_warnings( string( "Ivalid file format: there is a wrong symbol in the universe width: "

				+ to_string( s.at( i ) ) + "\n" ).data() );

		}

		if ( *width > ( float ) ( INT_MAX - ( s.at ( i ) - '0' ) ) / 10 ) {

			throw_exception_with_warnings( string( "Invalid file format: the universe width is too big, the maximal value is "

				+ to_string( INT_MAX ) + "\n" ).data() );

		}

		*width = *width * 10 + s.at ( i ) - '0';		

	}

	if ( 0 == *width ) {

		throw_exception_with_warnings( "Invalid file format: the universe width is 0, the minimal value is 1 \n" );

	}

	*height = 0;

	for( int i = spacePosition + 1; i < s.length(); i++ ) {

		if ( ( s.at( i ) < '0' ) || ( s.at( i ) > '9' ) ) {

			throw_exception_with_warnings( string ( "Ivalid file format: there is a wrong symbol in the universe height: "

				+ to_string( s.at( i ) ) + "\n" ).data() );

		}

		if ( *height > ( float ) ( INT_MAX - ( s.at ( i ) - '0' ) ) / 10 ) {

			throw_exception_with_warnings( string( "Invalid file format: the universe width is too big, the maximal value is "

				+ to_string( INT_MAX ) + "\n" ).data() );

		}

		*height = *height * 10 + s.at ( i ) - '0';		

	}

	if ( 0 == *height ) {

		throw_exception_with_warnings( "Invalid file format: the universe height is 0, the minimal value is 1 \n" );

	}

}

void Universe::readCoordinate( string s, vector< vector < bool > >* cells, int cellNumber ) {

	int spacePosition = s.find( " " ); 

	if ( -1 == spacePosition ) {

		throw_exception_with_warnings( string( "Ivalid file format: there is no space symbol in the coordinates of the cell number " 

			+ to_string( cellNumber  ) + "\n" ).data() );

	}

	int widthCoordinate = 0;

	bool widthNegative = ( '-' == s.at( 0 ) );

	for( int i = widthNegative; i < spacePosition; i++ ) {

		if ( ( s.at( i ) < '0' ) || ( s.at( i ) > '9' ) ) {

			throw_exception_with_warnings( string( "Ivalid file format: there is a wrong symbol in the width coordinate of the cell number "

				+ to_string( cellNumber ) + ": " + s.at( i ) + "\n" ).data() );

		}

		if ( widthCoordinate > ( float ) ( INT_MAX - ( s.at( i ) - '0' ) ) / 10 ) {

			throw_exception_with_warnings( string( "Invalid file format: the width coordinate of the cell number "

				+ to_string( cellNumber ) + " is too big, the maximal value is " + to_string( INT_MAX ) + "\n" ).data() );

		}

		widthCoordinate = widthCoordinate * 10 + s.at( i ) - '0';		

	}

	widthCoordinate = widthNegative ? -widthCoordinate : widthCoordinate;




	int heightCoordinate = 0;

	bool heightNegative = ( s.at( spacePosition + 1 ) == '-' );

	for( int i = spacePosition + 1 + heightNegative; i < s.length(); i++) {

		if ( ( s.at( i ) < '0' ) || ( s.at( i ) > '9' ) ) {

			throw_exception_with_warnings( string( "Ivalid file format: there is a wrong symbol in the height coordinate of the cell number " 

				+ to_string( cellNumber ) + ": " + s.at( i ) + "\n" ).data() );

		}

		if ( heightCoordinate > ( float ) ( INT_MAX - ( s.at( i ) - '0' ) ) / 10 ) {

			throw_exception_with_warnings( string( "Invalid file format: the height coordinate of the cell number "

				+ to_string( cellNumber ) + " is too big, the maximal value is " + to_string( INT_MAX ) + "\n" ).data() );

		}

		heightCoordinate = heightCoordinate * 10 + s.at( i ) - '0';

	}

	heightCoordinate = heightNegative ? -heightCoordinate : heightCoordinate;



	int width = ( *cells )[ 0 ].size();

	int height = ( *cells ).size();

	int endWidthCoordinate = ( width / 2 + widthCoordinate ) % width;

	int endHeightCoordinate =( height / 2 + heightCoordinate ) % height;

	if ( ( *cells )[ endHeightCoordinate ][ endWidthCoordinate ] ) {

		warnings += "Warning : the coordinates of the cell number " + to_string( cellNumber ) + " are repeating: " 

			+ to_string( widthCoordinate ) + " " + to_string( heightCoordinate ) + "\n";

	}

	( *cells )[ endHeightCoordinate ][ endWidthCoordinate ] = 1;

}

void Universe::dump( string inputString ) const {

	if ( 0 == inputString.length() ) {

		throw_exception_with_warnings( "Invalid input format: there is no output file name \n" );		

	}

	ofstream output ( inputString );

	if ( !output ) {

		throw_exception_with_warnings( string( "can not open the output file: " + inputString + "\n" + "please try to input another file name \n" ).data() );
		
	}

	output << "#Life 1.06\n";

	output << "#N " + universeName + "\n";

	output << "#R " + rulesToString() + "\n";	

	output << "#S " + to_string( width ) + " " + to_string( height ) + "\n";

	int originX;

	int originY;

	bool originSetted = false;

	for( int i = 0; i < height; i++ ) {

		for( int j = 0; j < width; j++ ) {

			if ( field->get_cells()[ i ][ j ] ) {

				if ( !originSetted ) {

					originX = j;

					originY = i;

					originSetted = true;

				}

				output << to_string( j - originX );

				output << " ";

				output << to_string( i - originY );

				output << "\n";

			}

		}

	}

	output.close();

}

Universe::Universe( string constructor_for_tests, string universeName, int width_, int height_, 
				   
				   vector< vector < bool > > cells_, bool birth_[ 9 ], bool survival_[ 9 ] ) {

	create_universe( universeName, width_, height_, cells_, birth_, survival_ );

}

void Universe::throw_exception_with_warnings( string s ) const {

	throw exception( string( warnings + s ).data() );

}




