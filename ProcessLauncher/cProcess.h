/**
	TODO: Class description
 */

#ifndef _C_PROCESS_
#define _C_PROCESS_

#include <string>
#include <memory>
#include <map>
#include <Windows.h>


class Process {

public:
	typedef std::shared_ptr< Process > proc_ptr;
	typedef std::map< std::string, std::list<Process> > proc_map;
	typedef std::pair< std::string, std::list<Process> > proc_pair;

	Process( std::wstring cmd, std::wstring cmdLine );
	~Process();
	std::wstring GetCommandLine();
	std::wstring GetCommand();
	int RunProcess();
	HANDLE GetProcessHandle();
	HANDLE GetThreadHandle();

private:
	std::wstring _cmd;
	std::wstring _cmdLine;
	int _args;
	HANDLE _hProc;
	HANDLE _hThread;
};

#endif