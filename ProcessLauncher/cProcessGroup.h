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
	ProcessGroup( std::list< Process > );
	~ProcessGroup()	{ }
	
	void LaunchProcessGroup();
	void AddProcess();
private:
	std::list< Process > _lst;
};

#endif