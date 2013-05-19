#ifndef _COMMON_H_
#define _COMMON_H_

#include <string>
#include <list>
#include "cProcess.h"
#include "cProcessGroup.h"

void ParseFile( char* fPath, Process::group &m );
void Run( Process::group_pair p, std::vector< LaunchReport > &reports );

#endif
