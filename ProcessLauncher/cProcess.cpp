#include <Windows.h>
#include <string>
#include "Common.h"
#include "cProcess.h"


/**
  Creates a new Process object.

  @param cmd
  The command to create the the new process.

  @param cmdLine
  The command line arguments passed when creating a new process.
 */
Process::Process( std::string cmd, std::string cmdLine ){
	this->_cmd = cmd;
	this->_cmdLine = cmdLine;
	this->_args = count_args( cmd );
}

/**
  Returns the command line used to create a new process.
 
  @return the module name for the process.
 */
std::string Process::GetCommandLine() {
	return _cmdLine;
}

/**
  Returns the command used to create a new process.
 
  @return the module name for the process.
 */
std::string Process::GetCommand() {
	return _cmd;
}

void Process::RunProcess() {
	std::wstring cmdLine = L"";	// Command line for the new process
	STARTUPINFO si;				// Pointer to a STARTUPINFO struct ...
    PROCESS_INFORMATION pi;		// Pointer to a PROCESS_INFORMATION struct that has handles to the new process.
	LPCWSTR imgName = LPCWSTR( _cmd.c_str() );	// The process to run
	LPWSTR proc_args = LPWSTR( (char)_args );	// The number of arguments

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
	
	BOOL proc = CreateProcess( 
		imgName,			// LPCWSTR pszImageName, 
		proc_args,			// LPWSTR pszCmdLine, 
		NULL,				// LPSECURITY_ATTRIBUTES psaProcess, 
		NULL,				// LPSECURITY_ATTRIBUTES psaThread, 
		FALSE,				// BOOL fInheritHandles, 
		CREATE_NEW_CONSOLE, // DWORD fdwCreate, 
		NULL,				// LPVOID pvEnvironment, 
		NULL,				// LPWSTR pszCurDir, 
		&si,				// LPSTARTUPINFOW psiStartInfo, 
		&pi 				// PROCESS_INFORMATION psiStartInfo
	); 

	unsigned long ret = WaitForSingleObject( pi.hProcess, INFINITE );

	if( ret == WAIT_OBJECT_0)
		;	// TODO: Something

	CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}