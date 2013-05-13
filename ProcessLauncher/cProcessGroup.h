/**
	TODO: Class description
 */

#ifndef _C_PROCESS_GROUP_
#define _C_PROCESS_GROUP_

#include <list>
#include "cProcess.h"

class ProcessGroup {

public:
	ProcessGroup()	{ }
	ProcessGroup( std::list< Process::proc_ptr > );
	~ProcessGroup()	{ }
	void LaunchProcessGroup();

private:
	std::list< Process::proc_ptr > _lst;
};

#endif