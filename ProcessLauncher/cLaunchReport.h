#ifndef _C_LAUNCH_REPORT_H
#define _C_LAUNCH_REPORT_H

#include <Windows.h>
#include <string>

class LaunchReport {

public:
	LaunchReport( int groupId,  int exitCode,  std::wstring progName, std::wstring progArgs ) 
		: _groupId(groupId), _exitCode(exitCode), _progName(progName), _progArgs(progArgs) { }
	~LaunchReport() { }
	SYSTEMTIME SetKernelTime( FILETIME &t );
	SYSTEMTIME SetUserTime( FILETIME &t );
	void SetExitCode( int code );
	SYSTEMTIME GetKernelTime();
	SYSTEMTIME GetUserTime();
	int GetExitCode();
	std::wstring GetProgramName();
	std::wstring GetProgramArgs();

private:
	int _groupId;
	int _exitCode;
	std::wstring _progName;
	std::wstring _progArgs;
	SYSTEMTIME _kTime;
	SYSTEMTIME _uTime;
};

#endif