#include "ProcessLauncherCommon.h"
#include "cLaunchReport.h"

using namespace std;

int main( int argc, char **argv ) {
	Process::group m;
	map< int, vector<LaunchReport> > reports;

	if( argc < 2 || argc > 2 ) {
		cout << "Error: Wrong number of arguments, exiting." << endl;
		return -1;
	}

	ParseFile( argv[1] , m );

	// Wrapper for ``Run`` function
	auto fn = [ &reports ]( Process::group_pair p ){ Run( p, reports ); };

	for_each( m.begin(), m.end(), fn );

	// Print the reports
	cout << "Launch Times" << endl;

	// Iterate over the ProcessGroups and display the ID
	for( auto it = reports.begin(); it != reports.end(); ++it ) {
		cout << endl << "G:" << it->first << endl;

		// Iterate over the reports and display them.
		for_each( it->second.begin(), it->second.end(), []( LaunchReport rep ) { wcout << rep; } );
	}

	cout << endl;

	return 0;
}