/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > jengine.h
*******************************************************/
#ifndef __JENGINE_H__
#define __JENGINE_H__

#include <pthread.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
using namespace std;

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>

#include "vmath.h"
#include "toolbox.h"
#include "user_interface.h"
#include "render.h"
#include "shader.h"
#include "mesh.h"
#include "entity.h"
#include "shape.h"
#include "camera.h"
#include "filter.h"
#include "scene.h"

namespace jengine {

///////////////////////////////////////////////// macros

#define SAFE_DELETE( obj ) { if( obj != nullptr ) { delete obj; obj = nullptr; } }
#define SAFE_DELETE_ARR( obj ) { if( obj != nullptr ) { delete [] obj; obj = nullptr; } }

///////////////////////////////////////////////// GLOBAL

namespace GLOBAL {
	// declared in jengine.cc

	extern void* engine_instance;
	extern void* setup_instance;
	extern timer stopwatch;

	extern unsigned short window_width;
	extern unsigned short window_height;

	extern ShaderSpec shader_spec;
}

///////////////////////////////////////////////// SETUP

struct SETUP {
	SETUP() {
		argc = nullptr;
		argv = nullptr;
		glut_display_mode = GLUT_RGBA;
		glut_ignore_key_repeat = true;
		glut_cursor = GLUT_CURSOR_NONE;
		window_title = "JEngine";
		window_width = 800;
		window_height = 600;
		default_render_distance_near = 1;
		default_render_distance_far = 100;
		quit_key = 0;
	}
	int* argc;
	char** argv;
	string window_title;
	unsigned int glut_display_mode;
	bool glut_ignore_key_repeat;
	unsigned int glut_cursor;
	unsigned short window_width;
	unsigned short window_height;
	float default_render_distance_near;
	float default_render_distance_far;
	unsigned int quit_key;
};

///////////////////////////////////////////////// JEngine

class JEngine {
public:
	JEngine( SETUP* setup );
	~JEngine();
	void stop();
	void start();

	// scene
	void add_scene( Scene* pS, bool load = false );
	void load_scene( Scene* pS );
	void load_scene( string name );
	void unload_scene();
	void destroy_scenes();

	// get
	vector< Scene* >* scenes();
	Scene* scene();
private:
	// glut callbacks
	static void callback_reshape( int w, int h );
	static void callback_display();
	static void callback_keydown( unsigned char key, int x, int y );
	static void callback_keyup( unsigned char key, int x, int y );
	static void callback_specialdown( int k, int x, int y );
	static void callback_specialup( int k, int x, int y );
	static void callback_mouse( int button, int state, int x, int y );
	static void callback_mousemove( int x, int y );
	static void callback_quit();

private:
	vector< Scene* > m_scenes;
	Scene* m_pScene;

};


} //jengine
#endif //__JENGINE_H__
