#include <iostream>

using namespace std;

int main( int argc, char** argv ) {
	if( argc < 3 || argc > 3 ) {
		cout << "Error: Wrong number of arguments, usage: looper <char> <repeat> " << endl;
		return -1;
	}

	for( int i = 0; i < atoi( argv[1] ); ++i )
		cout << argv[ 2 ];

	cout << endl;

	return 0;
}