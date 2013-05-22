#include <iostream>
#include <algorithm>
#include "ProcessLauncherCommon.h"
#include "cLaunchReport.h"

using namespace std;

int main( int argc, char **argv ) {
	Process::group m;
	vector< LaunchReport > reports;

	if( argc < 2 || argc > 2 ) {
		cout << "Error: Wrong number of arguments, exiting." << endl;
		return -1;
	}

	ParseFile( argv[1] , m );

	// Wrapper for ``Run`` function
	auto fn = [ &reports ]( Process::group_pair p ){ Run( p, reports ); };

	for_each( m.begin(), m.end(), fn );

	// Print the reports

	return 0;
}