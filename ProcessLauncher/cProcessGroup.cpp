#include "cProcessGroup.h"

/**
  Creates an empty ProcessGroup object.
 */
ProcessGroup::ProcessGroup( std::list< Process > grp ) {
	this->_lst = grp;
}


/**
  Launches the ProcessGroup concurrently and blocks until alll
  processes in the group return.
 */
void ProcessGroup::LaunchProcessGroup() {

}


void AddProcess() {
}