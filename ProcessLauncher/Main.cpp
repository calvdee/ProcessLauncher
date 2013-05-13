#include <iostream>
#include <algorithm>
#include <fstream> 
#include <assert.h>
#include <string>
#include <map>
#include <list>
#include <memory>
#include <sstream>
#include "cProcess.h"
#include "cProcessGroup.h"
#include "Common.h"

using namespace std;

//typedef shared_ptr< Process > proc_ptr;
//typedef map< string, list<Process> > proc_map;
//typedef pair< string, list<Process> > proc_pair;

void ParseFile( const string fName, Process::proc_map &m );
//void PrintReports( list< ProcessGroup > procs );

int main( int argc, char** argv ) {
	Process::proc_map m;
	list< ProcessGroup > procs;

	ParseFile( "infile.txt", m );

	// Function to create and launch the ProcessGroups using the 
	// lists of processes.
	auto fnRun = [ &procs ]( Process::proc_pair p ) {
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



void ParseFile( const string fName, Process::proc_map &m ) {
	ifstream in( fName );

	assert( in.is_open() );

	string grp, cmd, cmdLine;
	wstring wCmd, wCmdLine;

	while( !in.eof() ) {
		getline( in, grp, ',' );
		getline( in, cmd, ',' );
		getline( in, cmdLine, '\n' );

		wCmd = wstring( cmd.begin(), cmd.end() );
		wCmdLine = wstring( cmd.begin(), cmd.end() );

		m[ grp ].push_back( Process( wCmd, wCmdLine ) );
	};

	in.close();
}