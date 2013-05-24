#include "MainFunctions.h"
#include "cLaunchReport.h"

using namespace std;

int main( int argc, char **argv ) {
	Process::group procGroup;
	map< int, vector<LaunchReport> > reports;
	vector<wstring> errors;

	if( argc < 2 || argc > 2 ) {
		cout << "Error: Wrong number of arguments, exiting." << endl;
		return -1;
	}

	// Parse the file and build a map of processes where the key is the group ID
	// and the value is a vector of processes
	if( !ParseFile( argv[1] , procGroup ) ) {
		cout << "Error: Unable to open " << argv[1] << endl;
		return -1;
	}

	auto fn = [ &reports, &errors ]( Process::group_pair p ){ Run( p, reports, errors ); };

	// Serially run each vector of processes in the process group map
	for_each( procGroup.begin(), procGroup.end(), fn );

	// Print the reports
	cout << "Launch Times" << endl;

	for( auto it = reports.begin(); it != reports.end(); ++it ) {
		cout << endl << "G:" << it->first << endl;

		for_each( it->second.begin(), it->second.end(), []( LaunchReport rep ) { wcout << rep; } );
	}

	cout << endl;

	// Print the errors
	if( errors.size() > 0 ) {
		cout << "Exited with errors:" << endl;
		
		for_each( errors.begin(), errors.end(), []( wstring program ) { wcout << program << endl; } );
	}

	return 0;
}