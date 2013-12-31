#include <iostream>
#include <cmath>
#include <ctime>
#include <chrono>
using namespace std;

int main( int argc, char* argv[] ) {

	cout << "Benchmark sin vs. sqrt at " << CLOCKS_PER_SEC << " cycles/second" << endl;

	clock_t clock1, clock2;
	chrono::high_resolution_clock::time_point chrono1, chrono2;

	cout << "Running 100000000 sqrt calls (1234.0f)..." << endl;
	clock1 = clock();
	chrono1 = chrono::high_resolution_clock::now();
	for( int i = 0; i < 100000000; i++ ) {
		float f = sqrt( 1234.0f );
	}
	clock2 = clock();
	chrono2 = chrono::high_resolution_clock::now();
	cout << "CPU: " << clock2-clock1 << " cycles, Time: " << chrono::duration_cast< chrono::duration< float > >( chrono2-chrono1 ).count() << " seconds" << endl;
	

	cout << "Running 100000000 sin calls (M_PI/10.0f) ..." << endl;
	clock1 = clock();
	chrono1 = chrono::high_resolution_clock::now();
	for( int i = 0; i < 100000000; i++ ) {
		float f = sin( M_PI/10.0f );
	}
	clock2 = clock();
	chrono2 = chrono::high_resolution_clock::now();
	cout << "CPU: " << clock2-clock1 << " cycles, Time: " << chrono::duration_cast< chrono::duration< float > >( chrono2-chrono1 ).count() << " seconds" << endl;
	

	return 0;
}
