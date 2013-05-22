#include "cProcessGroup.h"
#include <iterator>
#include <vector>

/**
	Launches the ProcessGroup concurrently and blocks until all
	processes in the group return.

	@return a report object with ProcessGroup launch data.
 */
std::vector< LaunchReport > ProcessGroup::LaunchProcessGroup() {
	std::vector< HANDLE > running;
	std::vector< LaunchReport > reports;

	std::vector< Process::proc_ptr >::iterator it = _procs.begin();
	std::wstring cmd, args;
	int result = 0;

	for( ; it != _procs.end(); ++it ) {
		// Launch the process
		result = it->get()->RunProcess();
		cmd = it->get()->GetCommand();
		args = it->get()->GetCommandArgs();

		if( result != 0) {
			_errors.push_back( cmd );
			continue;
		}

		reports.push_back( LaunchReport( _id, result, cmd, args ) );
		running.push_back( it->get()->GetProcessHandle() );
	}

	// Block until all handles have signaled completion.
	//TODO: Error condition?
	DWORD wait = WaitForMultipleObjects( _procs.size(),
		running.data(),
		true,
		INFINITE );

	build_reports( running, reports );

	return reports;
}

/**
	
 */
void ProcessGroup::build_reports( std::vector<HANDLE>& handles, std::vector<LaunchReport>& reports ) {
	FILETIME createTime, exitTime, kernelTime, userTime;	
	DWORD exitCode;

	// Get the exit code and process times for each handle associated
	// with a runing process.
	for( size_t idx = 0; idx < handles.size(); ++idx ) {
		GetExitCodeProcess( handles[idx], &exitCode );
		GetProcessTimes( handles[idx], &createTime, &exitTime, &kernelTime, &userTime );
		
		reports[ idx ].SetKernelTime( kernelTime );
		reports[ idx ].SetUserTime( userTime );
		reports[ idx ].SetExitCode( exitCode );
	}
}
