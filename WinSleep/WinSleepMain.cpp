#include <iostream>
#include <Windows.h>

using namespace std;

int main( int argc, char** argv ) {
	if( argc < 2 || argc > 2 ) {
		cout << "Error: Wrong number of arguments, usage: winsleep <milliseconds> " << endl;
		return -1;
	}

	Sleep( atoi( argv[1] ) );

	return 0;
}