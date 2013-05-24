/**
	TODO: Class description
 */

#ifndef _C_PROCESS_
#define _C_PROCESS_

#include <string>
#include <memory>
#include <map>
#include <Windows.h>
#include <vector>

class Process {

public:
	typedef std::shared_ptr<Process> proc_ptr;
	typedef std::map< int, std::vector<Process::proc_ptr> > group;
	typedef std::pair< int, std::vector<Process::proc_ptr> > group_pair;

	Process( std::wstring cmd, std::wstring cmdArgs );
	~Process();
	std::wstring GetCommandArgs();
	std::wstring GetCommand();
	int RunProcess();
	HANDLE GetProcessHandle();
	DWORD GetPID();

private:
	std::wstring _cmd;
	std::wstring _cmdArgs;
	int _args;
	DWORD _pid;
	int count_args( std::wstring args );
	HANDLE _hProc;
	HANDLE _hThread;
};

#endif