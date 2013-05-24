/**
  * @purpose Launch a set of processes.  Processes that belong to the same group will
  *			 run concurrently.  The programs 
  *
  * @author Calvin De Lima
  * 
  * @date May 24, 2012
  */

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

	// Parse the file and build a map of programs where the key is the group ID
	// and the value is a vector of programs
	if( ParseFile( argv[1] , procGroup ) != 0) {
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
		cout << "Terminated With Error:\n\n";
		
		int i = 0;
		for_each( errors.begin(), errors.end(), [ &i ]( wstring program ) { wcout << ++i << ". " << program << endl; } );
	}

	cout << endl;

	return 0;
}