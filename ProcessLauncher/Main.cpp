#include <iostream>
#include <algorithm>
#include "ProcessLauncherCommon.h"

using namespace std;

int main( int argc, char** argv ) {
	Process::proc_map m;
	list< ProcessGroup > procs;

	ParseFile( "infile.txt", m );

	// Wrapper for ``Run`` function
	auto fn = [&procs]( Process::proc_pair p ){ Run( p, procs ); };

	for_each( m.begin(), m.end(), fn );

	// Print the reports
	//PrintReports( procs );
	return 0;
}