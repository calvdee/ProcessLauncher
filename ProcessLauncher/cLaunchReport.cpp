#include <Windows.h>
#include "cLaunchReport.h"

/**
  *	Sets the kernel time property for the report, converting
  *	`t` to SYSTEMTIME.
  *
  *	@param t
  *	The elapsed kernel time.
  *
  *	@return 
  * the kernel time as SYSTEMTIME
*/
SYSTEMTIME LaunchReport::SetKernelTime( FILETIME &t ) {
	FileTimeToSystemTime( &t, &_kTime );
	return _kTime;
}

/**
 * Sets the kernel time property for the report, converting
 * `t` to SYSTEMTIME.
 * 
 * @param t
 * The elapsed kernel time.
 * 
 * @return 
 * the kernel time as SYSTEMTIME
*/
SYSTEMTIME LaunchReport::SetUserTime( FILETIME &t ) {
	FileTimeToSystemTime( &t, &_uTime );
	return _uTime;
}

void LaunchReport::SetExitCode( int code )	{ _exitCode = code; }
SYSTEMTIME LaunchReport::GetKernelTime()	{ return _kTime; }
SYSTEMTIME LaunchReport::GetUserTime()		{ return _uTime; }
int LaunchReport::GetExitCode()				{ return _exitCode; }
int LaunchReport::GetGroupId()				{ return _groupID; }
std::wstring LaunchReport::GetProgramName()	{ return _progName; }
std::wstring LaunchReport::GetProgramArgs()	{ return _progArgs; }	