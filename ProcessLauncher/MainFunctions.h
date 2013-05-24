#ifndef _COMMON_H_
#define _COMMON_H_

#include <string>
#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
#include <assert.h>
#include <memory>
#include <algorithm>
#include <iomanip>
#include "cProcess.h"
#include "cProcessGroup.h"

int ParseFile( char* fPath, Process::group& m );
void Run( Process::group_pair p, std::map< int, std::vector<LaunchReport> >& reports, std::vector<std::wstring>& errors );
std::wostream& operator<<( std::wostream& o, LaunchReport report );
std::wostream& operator<<( std::wostream& o, SYSTEMTIME sysTime );

#endif
