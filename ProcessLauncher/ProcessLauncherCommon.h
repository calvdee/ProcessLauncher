#ifndef _COMMON_H_
#define _COMMON_H_

#include <string>
#include <list>
#include "cProcess.h"
#include "cProcessGroup.h"

void ParseFile( const std::string fName, Process::proc_map &m );
void Run( Process::proc_pair p, std::list< ProcessGroup > &lst );

#endif
