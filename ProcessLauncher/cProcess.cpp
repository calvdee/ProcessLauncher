#include <Windows.h>
#include <string>
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
}

/**
  Returns the command used to create a new process.
 
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
// Pointer to a null-terminated string that specifies the command line to execute.
	std::wstring cmdLine = L"";
	
	// Pointer to a PROCESS_INFORMATION structure that receives identification information about the new process.
	STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

	// The string can specify the full path and filename of the module to execute or it can specify a partial path and filename.		
	LPCWSTR imgName = L"..\\debug\\launchtarget.exe";

	// Command-line args
	LPWSTR proc_args = L"4";
	
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

	auto ret = WaitForSingleObject( pi.hProcess, INFINITE );

	if( ret == WAIT_OBJECT_0)
		cout << "Do something";

	CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}