/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > jengine.cc
*******************************************************/

#include "jengine.h"
namespace jengine {

///////////////////////////////////////////////// GLOBAL

void* GLOBAL::engine_instance = nullptr;
unsigned short GLOBAL::window_width = 800;
unsigned short GLOBAL::window_height = 600;
ShaderSpec GLOBAL::shader_spec;

///////////////////////////////////////////////// JEngine

JEngine::JEngine( const SETUP &setup ) {
	pthread_getconcurrency();
	GLOBAL::engine_instance = this;
	
	glutInit( setup.argc, setup.argv );
	glutInitDisplayMode( setup.glut_display_mode );
	glutInitContextVersion( 4, 3 );
	glutInitContextProfile( GLUT_CORE_PROFILE );

	GLOBAL::window_width = setup.window_width;
	GLOBAL::window_height = setup.window_height;
	glutInitWindowSize( setup.window_width, setup.window_height );
	glutInitWindowPosition( ( glutGet( GLUT_SCREEN_WIDTH )-setup.window_width )/2.0f, ( glutGet( GLUT_SCREEN_HEIGHT )-setup.window_height )/2.0f );
	glutCreateWindow( setup.window_title.c_str() );

	glewExperimental = GL_TRUE;
	if( glewInit() ) {
		cerr << __FILE__ << ":" << __LINE__ << ": Unable to initialize GLEW." << endl;
		exit( 1 );
	}

	glutReshapeFunc( JEngine::callback_reshape );
	glutDisplayFunc( JEngine::callback_display );
	atexit( JEngine::callback_quit );
	
	glutIgnoreKeyRepeat( ( setup.glut_ignore_key_repeat )?1:0 );
	glutKeyboardFunc( JEngine::callback_keydown );
	glutKeyboardUpFunc( JEngine::callback_keyup );
	glutSpecialFunc( JEngine::callback_specialdown );
	glutSpecialUpFunc( JEngine::callback_specialup );

	glutSetCursor( setup.glut_cursor );
	glutMouseFunc( JEngine::callback_mouse );
	glutPassiveMotionFunc( JEngine::callback_mousemove );

	INPUT::quit_key = setup.quit_key;

	m_pScene = nullptr;
}

JEngine::~JEngine() {
	stop();
}

void JEngine::stop() {
	destroy_scenes();
}

void JEngine::start() {
	glutMainLoop();
}

//----------------- scene

void JEngine::add_scene( Scene* pS, bool load ) {
	if( pS == nullptr ) {
		cerr << __FILE__ << ":" << __LINE__ << ": Not adding NULL scene (" << pS << ")." << endl;
		return;
	}
	m_scenes.push_back( pS );
	if( load ) load_scene( pS );
}

void JEngine::load_scene( Scene* pS ) {
	if( pS == nullptr ) {
		cerr << __FILE__ << ":" << __LINE__ << ": Not loading NULL scene (" << pS << ")." << endl;
		return;
	}
	if( m_pScene != nullptr ) m_pScene->base_unload();
	m_pScene = pS;
	m_pScene->base_load();
}

void JEngine::load_scene( string name ) {
	for( unsigned int i = 0; i < m_scenes.size(); i++ ) {
		if( TOOL::streq( name, m_scenes[i]->name() ) ) {
			load_scene( m_scenes[i] );
			return;
		}
	}
	cerr << __FILE__ << ":" << __LINE__ << ": Could not find scene (" << name << ")." << endl;
}

void JEngine::unload_scene() {
	if( m_pScene == nullptr ) return;
	m_pScene->base_unload();
	m_pScene = nullptr;
}

void JEngine::destroy_scenes() {
	unload_scene();
	m_scenes.clear();
}

//----------------- get

vector< Scene* >* JEngine::scenes() { return &m_scenes; }
Scene* JEngine::scene() { return m_pScene; }


//----------------- glut callbacks

void JEngine::callback_reshape( int w, int h ) {
	glViewport( 0, 0, w, h );
	GLOBAL::window_width = w;
	GLOBAL::window_height = h;
	if( ( (JEngine*)(GLOBAL::engine_instance ) )->scene() != nullptr ) {
		( (JEngine*)(GLOBAL::engine_instance ) )->scene()->reshape();
	}
}

void JEngine::callback_display() {
	TIMER::calculate_delta();
	JEngine* pE = (JEngine*)(GLOBAL::engine_instance);
	if( pE->scene() != nullptr ) {
		pE->scene()->update();
		if( pE->scene()->camera() != nullptr ) {
			pE->scene()->camera()->update();
			pE->scene()->camera()->apply();
		}
		pE->scene()->render();
	}
	INPUT::reset_events();
}

void JEngine::callback_keydown( unsigned char key, int x, int y ) {
	if( INPUT::quit_key > 0 && INPUT::quit_key == (unsigned int)key ) {
		( (JEngine*)(GLOBAL::engine_instance ) )->stop();
		exit( 0 );
	}
	INPUT::key[(unsigned int)key] = true;
	INPUT::key_down = (int)key;
}
void JEngine::callback_keyup( unsigned char key, int x, int y ) {
	INPUT::key[(unsigned int)key] = false;
	INPUT::key_up = (int)key;
}

void JEngine::callback_specialdown( int key, int x, int y ) {
	INPUT::special[(unsigned int)key] = true;
	INPUT::special_down = key;
}
void JEngine::callback_specialup( int key, int x, int y ) {
	INPUT::special[(unsigned int)key] = false;
	INPUT::special_up = key;
}

void JEngine::callback_mouse( int button, int state, int x, int y ) {
	if( button < 0 || button >= 10 ) button = 9;
	unsigned int btn = (unsigned int)button;
	switch( state ) {
		case GLUT_DOWN:
			INPUT::mouse[btn] = true;
			INPUT::mouse_down = button;
			break;
		case GLUT_UP:
			INPUT::mouse[btn] = false;
			INPUT::mouse_up = button;
			break;
		default:
			cerr << __FILE__ << ":" << __LINE__ << ": Unrecognized mouse state (" << state << ")." << endl;
	}
}
void JEngine::callback_mousemove( int x, int y ) {
	INPUT::move_mouse( (short)x, (short)y );
}

void JEngine::callback_quit() {
	( (JEngine*)(GLOBAL::engine_instance ) )->stop();
}

} //jengine
