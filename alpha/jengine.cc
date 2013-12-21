/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > jengine.cc
*******************************************************/

#include "jengine.h"
namespace jengine {

// GLOBAL
bool GLOBAL::debug = false;
unsigned short GLOBAL::window_width = 800;
unsigned short GLOBAL::window_height = 600;


///////////////////////////////////////////////// JEngine

JEngine::JEngine( const SETUP &c ) {
	pthread_getconcurrency();
	
	glutInit( c.argc, c.argv );
	glutInitDisplayMode( c.glut_display_mode );
	glutInitContextVersion( 4, 3 );
	glutInitContextProfile( GLUT_CORE_PROFILE );

	GLOBAL::window_width = c.window_width;
	GLOBAL::window_height = c.window_height;
	glutInitWindowSize( c.window_width, c.window_height );
	glutCreateWindow( c.window_title.c_str() );

	glewExperimental = GL_TRUE;
	if( glewInit() ) {
		cerr << __FILE__ << ":" << __LINE__ << ": Unable to initialize GLEW." << endl;
		exit( 1 );
	}

	glutReshapeFunc( JEngine::callback_reshape );
	glutDisplayFunc( JEngine::callback_display );
}

JEngine::~JEngine() {
	stop();
}

void JEngine::stop() {
	
}

void JEngine::start() {
	glutMainLoop();
}

void JEngine::callback_reshape( int w, int h ) {

}

void JEngine::callback_display() {

}

}
