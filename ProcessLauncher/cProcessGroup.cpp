#include "cProcessGroup.h"
#include <iterator>
#include <vector>

/**
  Creates an empty ProcessGroup object.
 */
ProcessGroup::ProcessGroup( std::list< Process::proc_ptr > grp ) {
	this->_lst = grp;
}


/**
  Launches the ProcessGroup concurrently and blocks until alll
  processes in the group return.
 */
void ProcessGroup::LaunchProcessGroup() {
	DWORD nCount = _lst.size();
	std::vector< HANDLE > vRunning;

	std::list< Process::proc_ptr >::iterator it = _lst.begin();
	for( ; it != _lst.end(); ++it ) {
		// Launch the process

		if( it->get()->RunProcess() != 0) {
			// TODO: Print to std err.
		}

		vRunning.push_back( it->get()->GetProcessHandle() );
	}

	// Block until all handles have signaled completion.
	DWORD ret = WaitForMultipleObjects( nCount,	// _In_  DWORD nCount
		vRunning.data(),	// _In_  const HANDLE *lpHandles
		true,				// _In_  BOOL bWaitAll
		INFINITE			// _In_  DWORD dwMilliseconds
	);

}

