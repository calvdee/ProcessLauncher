#include "cProcessGroup.h"
#include "MainFunctions.h"

/**
	Parse the input file formatted:
	<LaunchGroup>,<Command>,<arg0>, ... , <argN>

	@param fPath
	The path to the input file.

	@param procMap
	A reference to a process map with key of process group ID
	and value is a vector of Processes associated with the group.
  */
int ParseFile( char* fPath, Process::group& procMap ) {
	std::ifstream in( fPath );
	
	if( !in.is_open() )
		return -1;

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

		procMap[ atoi( (char*)(&group) ) ].push_back( std::make_shared<Process>( wProg, wArgs ) );
	};

	in.close();

	return 0;
}

/**
  * Create `ProcessGroup` from list of Processes and Launch them.  Then
  * add the process to the list.
  * 
  * @param group
  * The <GroupIdentifier><ListOfProcesses> `pair<K, V>` data structure from which
  * a ProcessGroup is created.
  * 
  * @param reports
  * A map or LaunchReport objects indexed by the group ID.
  * 
  * @param errors
  * If a process terminated with error, it will be added to this vector.
  */
void Run( Process::group_pair group, std::map< int, std::vector<LaunchReport> >& reports, std::vector<std::wstring>& errors )
{
	ProcessGroup procGroup( group.first, group.second );
	std::vector< LaunchReport > gReports = procGroup.LaunchProcessGroup();

	// Add the report to the map using process group ID as the index. If the process terminated
	// with error, add it the errors vector.
	std::for_each( gReports.begin(), gReports.end(), [ &reports, &errors, group ]( LaunchReport report ) { 
		if(report.GetExitCode() < 0) {
			errors.push_back( report.GetProgramName() );
			return;
		}

		reports[group.first].push_back( report );
	} );
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