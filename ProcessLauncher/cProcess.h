/**
	TODO: Class description
 */

#ifndef _C_PROCESS_
#define _C_PROCESS_

#include <string>

class Process {

public:
	Process( std::string cmd, std::string cmdLine );
	~Process()	{ }
	std::string GetCommandLine();
	std::string GetCommand();

private:
	std::string _cmd;
	std::string _cmdLine;
};

#endif