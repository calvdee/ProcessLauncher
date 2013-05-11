#include <iostream>
#include <algorithm>
#include <fstream> 
#include <assert.h>
#include <string>
#include <map>
#include <list>
#include <memory>
#include "cProcess.h"
#include "cProcessGroup.h"

using namespace std;

typedef shared_ptr< Process > proc_ptr;
typedef map< string, list<Process> > proc_map;
typedef pair< string, list<Process> > proc_pair;

void ParseFile( const string fName, proc_map &m );
//void PrintReports( list< ProcessGroup > procs );

int main( int argc, char** argv ) {
	proc_map m;
	list< ProcessGroup > procs;
	ParseFile( "infile.txt", m );

	// Function to create and launch the ProcessGroups
	auto fnRun = [ &procs ]( proc_pair p ) {
		ProcessGroup grp( p.second );
		grp.LaunchProcessGroup();
		procs.push_back( grp );
	};

	// Create and run the ProcessGroups
	for_each( m.begin(), m.end(), fnRun );

	// Print the reports
	//PrintReports( procs );

	return 0;
}

void ParseFile( const string fName, proc_map &m ) {
	ifstream in( fName );

	assert( in.is_open() );

	string grp, cmd, cmdLine;

	while( !in.eof() ) {
		getline( in, grp, ',' );
		getline( in, cmd, ',' );
		getline( in, cmdLine, '\n' );

		m[ grp ].push_back( Process(cmd, cmdLine) );
	};

	in.close();
}