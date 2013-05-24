/**
  * @purpose A class used to encapsulate launched process report data.
  *
  * @author Calvin De Lima
  * 
  * @date May 24, 2012
  */
#ifndef _C_LAUNCH_REPORT_H
#define _C_LAUNCH_REPORT_H

#include <Windows.h>
#include <string>
#include <ostream>

class LaunchReport {

public:
	LaunchReport( int groupId,  int exitCode,  std::wstring progName, std::wstring progArgs ) 
		: _groupID(groupId), _exitCode(exitCode), _progName(progName), _progArgs(progArgs) { }
	~LaunchReport() { }
	SYSTEMTIME SetKernelTime( FILETIME& t );
	SYSTEMTIME SetUserTime( FILETIME& t );
	void SetExitCode( int code );
	SYSTEMTIME GetKernelTime();
	SYSTEMTIME GetUserTime();
	int GetExitCode();
	int GetGroupId();
	std::wstring GetProgramName();
	std::wstring GetProgramArgs();

private:
	int _groupID;
	int _exitCode;
	std::wstring _progName;
	std::wstring _progArgs;
	SYSTEMTIME _kTime;
	SYSTEMTIME _uTime;
};

#endif