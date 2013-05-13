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
void Run( Process::proc_pair p, list< ProcessGroup > &lst );
//void PrintReports( list< ProcessGroup > procs );

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


/**
	Parse the input file formatted:
	<LaunchGroup>,<Command>,<arg0>, ... , <argN>

	@param fPath
	The path to the input file.

	@param m
	A reference to a process map with key of process group identifer
	and value is a list of Processes associated with the group.
  */
void ParseFile( const string fPath, Process::proc_map &m ) {
	ifstream in( fPath );

	assert( in.is_open() );

	string grp, cmd, cmdLine;
	wstring wCmd, wCmdLine;

	while( !in.eof() ) {
		getline( in, grp, ',' );
		getline( in, cmd, ',' );
		getline( in, cmdLine, '\n' );

		wCmd = wstring( cmd.begin(), cmd.end() );
		wCmdLine = wstring( cmd.begin(), cmd.end() );

		m[ grp ].push_back( Process::proc_ptr( new Process(wCmd, wCmdLine) ) );
	};

	in.close();
}

/**
	Create ``ProcessGroup`` from list of Processes and Launch them.  Then
	add the process to the list.

	@param p
	The <GroupIdentifier><ListOfProcesses> data structure from which we
	create the ProcessGroup.

	@param lst
	A reference to a list in which the created and running or finished process
	is added to.
  */
void Run( Process::proc_pair p, list< ProcessGroup > &lst )
{
		// Create the ``ProcessGroup`` and start it up
		ProcessGroup grp( p.second );
		grp.LaunchProcessGroup();

		// Add to the container
		lst.push_back( grp );
}