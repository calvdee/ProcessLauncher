#include <sstream>
#include "Common.h"

/**
  Counts the arguments

  @param args
  The string containing command line arguments
 */
int count_args( std::string args ) {
	int i = 0;
	std::string arg;
	std::istringstream iss( args );

	while( iss >> arg ) { ++i; };

	return i;
}