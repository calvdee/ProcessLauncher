#include "cProcessGroup.h"
#include <iterator>

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
	HANDLE lpHandles[256] = { 0 };
	int idx = -1;

	// TODO: Iterate over list of ``Process`` objects and launch them then
	//       wait for their created handles using `GetHandle` method.

	std::list< Process::proc_ptr >::iterator it = _lst.begin();

	for( ; it != _lst.end(); ++it )
	{
		// Launch the process
		if( it->get()->RunProcess() != 0) {
			// TODO: Print to std err.
		}

		// 2. GetProcess()
		lpHandles[ ++idx ] = it->get()->GetProcessHandle();
	}

	// 3. Block until the handles are signaled.
	DWORD ret = WaitForMultipleObjects(nCount,// _In_  DWORD nCount
		lpHandles,	// _In_  const HANDLE *lpHandles
		true,		// _In_  BOOL bWaitAll
		INFINITE	// _In_  DWORD dwMilliseconds
	);

}

