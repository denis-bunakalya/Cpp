#ifndef model_h
#define model_h

#include <vector>

#include "strategy.h"

enum Game_mode { detailed, fast, tournament };

class Model {	

public:

	// Constructor for the command line input arguments
	Model( int argc, char** argv );

	// Constructor for the tournament mode
	Model( std::vector< std::string >& strategies_ );

	// Destructor
	~Model();

	// Calculates the next state of the model
	void next();

	// Returns the game mode
	const Game_mode& get_game_mode() const;

	// Returns the strategy names
	const std::string* get_strategy_names() const;

	// Returns the current step
	const int& get_current_step() const;

	// Returns the current decisions
	const bool* get_current_decisions() const;	

	// Returns the current points
	const int* get_current_points() const;

	// Returns the game points
	const int* get_game_points() const;

private:

	Game_mode game_mode;

	Strategy* strategies[ 3 ];

	std::string strategy_names[ 3 ];

	int current_step;

	bool current_decisions[ 3 ];

	int current_points[ 3 ];

	int game_points[ 3 ];	

	// Constructs the model for the strategies with the names from the vector of strings "strategies_"
	void create_model( std::vector< std::string >& strategies_ );

	// Reads the matrix for the game from the file with name "filename"
	void read_matrix( std::string& filename );

};

static int matrix[ 8 ][ 3 ] = { 
	{ 1, 1, 1 },
	{ 3, 3, 0 },
	{ 3, 0, 3 },
	{ 5, 2, 2 },
	{ 0, 3, 3 },
	{ 2, 5, 2 },
	{ 2, 2, 5 },
	{ 4, 4, 4 } };

#endif