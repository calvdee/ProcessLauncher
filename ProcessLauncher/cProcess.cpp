#include <string>
#include <sstream>
#include "cProcess.h"


/**
	Creates a new Process object.

	@param cmd
	The command to create the the new process.

	@param cmdLine
	The command line arguments passed when creating a new process.
 */
Process::Process( std::wstring cmd, std::wstring cmdLine ){
	this->_cmd = cmd;
	this->_cmdArgs = cmdLine;
	this->_args = count_args( cmd );
	this->_hProc = NULL;
	this->_hThread = NULL;
	this->_pid = -1;
}

/**
	Closes the thread and process handles.
 */
Process::~Process() {
	CloseHandle( this->_hProc );
	CloseHandle( this->_hThread );
}

/**
	Returns the command line used to create a new process.
 
	@return the module name for the process.
 */
std::wstring Process::GetCommandArgs() { return _cmdArgs; }

/**
	Returns the command used to create a new process.
 
	@return the module name for the process.
 */
std::wstring Process::GetCommand() { return _cmd; }

/**
	Returns the handle to the process.

	@return the process's handle if the process has been created, otherwise NULL.
 */
HANDLE Process::GetProcessHandle() { return this->_hProc; }

/**
	Returns the process ID of the process.

	@return the process's PID if it was created succesfully otherwise -1.
 */
DWORD Process::GetPID() { return this->_pid; }

/**
	Executes the CreateProcesss() system call to starta new process.

	@return 0 if the process was created successfully or the error
	code if the call failed.
*/
int Process::RunProcess() {
	STARTUPINFO si = { 0 };			// Pointer to a STARTUPINFO struct ...
	PROCESS_INFORMATION pi = { 0 };	// Pointer to a PROCESS_INFORMATION struct that has handles to the new process.
	LPCWSTR imgName = _cmd.c_str();	// The process to run

	// TODO: add quotes in case of spaces
	LPWSTR cmdArgs = const_cast< LPWSTR >( _cmdArgs.c_str() );	// Command line for the new process 

    si.cb = sizeof(STARTUPINFO);
	
	BOOL success;
	try {
		success = CreateProcess( imgName,	// LPCWSTR pszImageName, 
			cmdArgs,			// LPWSTR pszCmdLine, 
			NULL,				// LPSECURITY_ATTRIBUTES psaProcess, 
			NULL,				// LPSECURITY_ATTRIBUTES psaThread, 
			FALSE,				// BOOL fInheritHandles, 
			CREATE_NEW_CONSOLE, // DWORD fdwCreate, 
			NULL,				// LPVOID pvEnvironment, 
			NULL,				// LPWSTR pszCurDir, 
			&si,				// LPSTARTUPINFOW psiStartInfo, 
			&pi 				// PROCESS_INFORMATION psiStartInfo
		); 
	}
	catch( std::bad_alloc ) {
		return -1;
	}
	
	// Return the error code

	if( !success )
		return GetLastError();

	_hProc = pi.hProcess;
	_hThread = pi.hThread;
	_pid = pi.dwProcessId;

	return 0;
}

/**
  Counts the arguments

  @param args
  The string containing command line arguments
 */
int Process::count_args( std::wstring args ) {
	int i = 0;
	std::wstring arg;
	std::wistringstream iss( args );
	
	while( iss >> arg ) { ++i; };

	return i;
}