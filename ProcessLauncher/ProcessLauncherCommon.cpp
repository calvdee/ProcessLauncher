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
void ParseFile( char* fPath, Process::group &m ) {
	std::ifstream in( fPath );

	// TODO: Handle this properly
	assert( in.is_open() );

	char group;
	std::string cmd, args;
	std::wstring wProg, wArgs;

	while( !in.eof() ) {
		group = in.get();
		
		if( !in.good() )
			continue;
		
		in.get(); // Discard `,`
		getline( in, cmd, ',' );
		getline( in, args, '\n' );
		
		wProg = std::wstring( cmd.begin(), cmd.end() );
		wArgs = std::wstring( args.begin(), args.end() );

		m[ atoi( (char*)(&group) ) ].push_back( std::make_shared<Process>( wProg, wArgs ) );
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
void Run( Process::group_pair p, std::map< int, std::vector<LaunchReport> > &reports )
{
	// Create the `ProcessGroup` and start it up with the ID and list of processes.
	ProcessGroup procGroup( p.first, p.second );
	std::vector< LaunchReport > gReports = procGroup.LaunchProcessGroup();

	// Add the report to the map using process group ID as the index.
	std::for_each( gReports.begin(), gReports.end(), 
		[ &reports, p ]( LaunchReport report ) { reports[p.first].push_back( report ); } );
}

std::wostream& operator<<( std::wostream& o, LaunchReport report ) {
	o << L"K:" << report.GetKernelTime()	<< " "
	  << L"U:" << report.GetUserTime()	<< " "
	  << L"E:" << report.GetExitCode()	<< " "
	  << L"G:" << report.GetGroupId()	<< " "
	  << report.GetProgramName() << " "
	  << report.GetProgramArgs() << std::endl;

	return o;
}

std::wostream& operator<<( std::wostream& o, SYSTEMTIME sysTime ) {
	o << std::setw( 2 ) << std::setfill( L'0' ) << sysTime.wHour << L":" 
	  << std::setw( 2 ) << std::setfill( L'0' ) << sysTime.wMinute << L":" 
	  << std::setw( 2 ) << std::setfill( L'0' ) << sysTime.wSecond << L"."
	  << std::setw( 3 ) << std::setfill( L'0' ) << sysTime.wMilliseconds;

	return o;
}