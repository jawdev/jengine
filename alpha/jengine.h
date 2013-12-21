/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > jengine.h
*******************************************************/

#ifndef __JENGINE_H__
#define __JENGINE_H__

#include <pthread.h>
#include <iostream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>

using namespace std;



///////////////////////////////////////////////// JEngine
namespace jengine {

namespace GLOBAL {
	// declared in jengine.cc

	extern bool debug;

	extern unsigned short window_width;
	extern unsigned short window_height;
}

struct SETUP {
	SETUP() {
		argc = nullptr;
		argv = nullptr;
		window_width = 800;
		window_height = 600;
		window_title = "JEngine";
		glut_display_mode = GLUT_RGBA;
	}
	int* argc;
	char** argv;
	unsigned short window_width;
	unsigned short window_height;
	string window_title;
	unsigned int glut_display_mode;
};

class JEngine {
public:
	JEngine( const SETUP &c );
	~JEngine();
	void stop();
	void start();

private:
	static void callback_reshape( int w, int h );
	static void callback_display();

};


} //jengine
#endif //__JENGINE_H__
