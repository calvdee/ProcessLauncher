/**
	TODO: Class description
 */

#ifndef _C_PROCESS_GROUP_
#define _C_PROCESS_GROUP_

#include "cProcess.h"
#include "cLaunchReport.h"

class ProcessGroup {

public:
	ProcessGroup( int id, std::vector<Process::proc_ptr> procs )
		: _id( id ), _procs( procs ) { }
	~ProcessGroup()	{ }
	std::vector< LaunchReport > LaunchProcessGroup();

private:
	int _id;
	std::vector< Process::proc_ptr > _procs;
	std::vector< std::wstring > _errors;
	void build_reports( std::vector<HANDLE>& handles, std::vector<LaunchReport>& reports );
};

#endif