/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > toolbox.h
*******************************************************/
#ifndef __JENGINE_TOOLBOX_H__
#define __JENGINE_TOOLBOX_H__
namespace jengine {

///////////////////////////////////////////////// timer

struct timer {

	timer() {
		last_time = chrono::high_resolution_clock::now();
		delta = 0;
	}

	float time_since_epoch() {
		chrono::high_resolution_clock::time_point t = chrono::high_resolution_clock::now();
		return float( chrono::duration_cast< chrono::duration< float > >( t.time_since_epoch() ).count() );
	}

	float calculate_delta() {
		chrono::high_resolution_clock::time_point t = chrono::high_resolution_clock::now();
		delta = float( chrono::duration_cast< chrono::duration< float > >( t-last_time ).count() );
		last_time = t;
		return delta;
	}

	unsigned int fps() {
		if( delta == 0 ) return 0;
		return (unsigned int)1.0f/delta;
	}

	chrono::high_resolution_clock::time_point last_time;
	float delta;

};


///////////////////////////////////////////////// TOOL

namespace TOOL {

	static inline bool streq( string s1, string s2 ) {
		return ( s1.compare( s2 ) == 0 );
	}

	static inline char* file_get_contents( const char* filename, bool zero_term = false ) {
		ifstream in( filename, ios::in|ios::binary );
		if( !in ) {
			cerr << __FILE__ << ":" << __LINE__ << ": File could not be read (" << filename << ")." << endl;
			exit( 1 );
		}
		char* contents;
		in.seekg( 0, ios::end );
		unsigned int len = (unsigned int)in.tellg();
		contents = new char[len+1];
		in.seekg( 0, ios::beg );
		in.read( contents, len );
		in.close();
		if( zero_term ) contents[len] = 0;
		return contents;
	}

} //TOOL

}//jengine
#endif //__JENGINE_TOOLBOX_H__
