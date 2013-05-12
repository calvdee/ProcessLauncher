#include <sstream>
#include "Common.h"

/**
  Counts the arguments

  @param args
  The string containing command line arguments
 */
int count_args( std::wstring args ) {
	int i = 0;
	std::wstring arg;
	std::wistringstream iss( args );
	
	while( iss >> arg ) { ++i; };

	return i;
}