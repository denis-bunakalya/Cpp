#include "controller.h"

int main( int argc, char** argv ) {

	try {

	Controller controller ( argc, argv );

	} catch ( ... ) {

		exit( 1 );

	}

}