#include "cProcessGroup.h"

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
	HANDLE *lpHandles = NULL;
	int idx = -1;

	// TODO: Iterate over list of ``Process`` objects and launch them then
	//       wait for their created handles using `GetHandle` method.

	// for each process:
		// 1. Launch

		// 2. GetProcess()

		// 3. Block until the handles are signaled.
		DWORD ret = WaitForMultipleObjects(
		  nCount,		// _In_  DWORD nCount
		  lpHandles,	// _In_  const HANDLE *lpHandles
		  true,			// _In_  BOOL bWaitAll
		  0				// _In_  DWORD dwMilliseconds
		);


}

