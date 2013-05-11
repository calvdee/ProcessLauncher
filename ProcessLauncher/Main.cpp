#include <iostream>
#include <algorithm>
#include <fstream> 
#include <assert.h>
#include <string>
#include <map>
#include <list>
#include <memory>
#include "cProcess.h"
#include "cProcessGroup.h"

using namespace std;

typedef shared_ptr< Process > proc_ptr;
typedef map< string, list<Process> > proc_map;
typedef pair< string, list<Process> > proc_pair;

void ParseFile( proc_map &m );

int main( int argc, char** argv ) {
	proc_map m;
	list< ProcessGroup > procs;

	ParseFile( m );

	auto fn = [ &procs ]( proc_pair p ) {
		procs.push_back( ProcessGroup(p.second) );
	};

	for_each( m.begin(), m.end(), fn );

	return 0;
}

void ParseFile( proc_map &m ) {
	ifstream _file( "infile.txt" );

	assert( _file.is_open() );

	string grp, cmd, cmdLine;

	while( !_file.eof() ) {
		getline( _file, grp, ',' );
		getline( _file, cmd, ',' );
		getline( _file, cmdLine, '\n' );

		m[ grp ].push_back( Process(cmd, cmdLine) );
	};

	_file.close();
}