/**
	TODO: Class description
 */

#ifndef _C_PROCESS_
#define _C_PROCESS_

#include <string>
#include <memory>
#include <map>
#include <Windows.h>
#include <list>

class Process {

public:
	typedef std::shared_ptr< Process > proc_ptr;
	typedef std::map< std::string, std::list<Process::proc_ptr> > proc_map;
	typedef std::pair< std::string, std::list<Process::proc_ptr> > proc_pair;

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
	int count_args( std::wstring args );
	HANDLE _hProc;
	HANDLE _hThread;

};

#endif