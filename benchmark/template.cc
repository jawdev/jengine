#include <iostream>
#include <cmath>
#include <ctime>
#include <chrono>
using namespace std;

int main( int argc, char* argv[] ) {

	cout << "Benchmark at " << CLOCKS_PER_SEC << " clocks/second" << endl;

	clock_t clock1, clock2;
	chrono::high_resolution_clock::time_point chrono1, chrono2;

	cout << "Running..." << endl;
	clock1 = clock();
	// operation goes here
	clock2 = clock();
	chrono2 = chrono::high_resolution_clock::now();
	cout << "CPU: " << clock2-clock1 << " clocks, Time: " << chrono::duration_cast< chrono::duration< float > >( chrono2-chrono1 ).count() << " seconds" << endl;
	
	return 0;
}
