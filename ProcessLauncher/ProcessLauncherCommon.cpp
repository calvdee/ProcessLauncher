#include <sstream>
#include <fstream>
#include <assert.h>
#include <memory>
#include "cProcessGroup.h"
#include "ProcessLauncherCommon.h"

/**
	Parse the input file formatted:
	<LaunchGroup>,<Command>,<arg0>, ... , <argN>

	@param fPath
	The path to the input file.

	@param m
	A reference to a process map with key of process group identifer
	and value is a list of Processes associated with the group.
  */
void ParseFile( const std::string fPath, Process::proc_map &m ) {
	std::ifstream in( fPath );

	// TODO: Handle this properly
	assert( in.is_open() );

	std::string grp, cmd, cmdLine;
	std::wstring wCmd, wCmdLine;

	while( !in.eof() ) {
		getline( in, grp, ',' );
		getline( in, cmd, ',' );
		getline( in, cmdLine, '\n' );

		wCmd = std::wstring( cmd.begin(), cmd.end() );
		wCmdLine = std::wstring( cmd.begin(), cmd.end() );

		//m[ grp ].push_back( Process::proc_ptr( new Process(wCmd, wCmdLine) ) );
		m[ grp ].push_back( std::make_shared< Process >( wCmd, wCmdLine ) );
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
void Run( Process::proc_pair p, std::list< ProcessGroup > &lst )
{
		// Create the ``ProcessGroup`` and start it up
		ProcessGroup grp( p.second );
		grp.LaunchProcessGroup();

		// Add to the container
		lst.push_back( grp );
}