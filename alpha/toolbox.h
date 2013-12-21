/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > toolbox.h
*******************************************************/
#ifndef __JENGINE_TOOLBOX_H__
#define __JENGINE_TOOLBOX_H__
namespace jengine {

///////////////////////////////////////////////// TIMER

namespace TIMER {

	static chrono::high_resolution_clock::time_point last_time = chrono::high_resolution_clock::now();
	static float delta = 0;

	static inline float time_since_epoch() {
		chrono::high_resolution_clock::time_point t = chrono::high_resolution_clock::now();
		return float( chrono::duration_cast< chrono::duration< float > >( t.time_since_epoch() ).count() );
	}

	static inline float calculate_delta() {
		chrono::high_resolution_clock::time_point t = chrono::high_resolution_clock::now();
		delta = float( chrono::duration_cast< chrono::duration< float > >( t-last_time ).count() );
		last_time = t;
		return delta;
	}

	static inline unsigned int fps() {
		if( delta == 0 ) return 0;
		return (unsigned int)1.0f/delta;
	}

}


///////////////////////////////////////////////// TOOL

namespace TOOL {

	static inline bool streq( string s1, string s2 ) {
		return ( s1.compare( s2 ) == 0 );
	}

} //TOOL

}//jengine
#endif //__JENGINE_TOOLBOX_H__
