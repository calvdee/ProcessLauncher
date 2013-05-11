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
