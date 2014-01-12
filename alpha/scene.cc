/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > scene.cc
*******************************************************/
#include "jengine.h"
namespace jengine {

///////////////////////////////////////////////// Scene

Scene::Scene( string name ) {
	m_enabled = new bool[SCENE_ENABLE_LEN];
	enable_defaults();
	m_name = name;
	m_pRenderbuffer = nullptr;
	m_pCamera = nullptr;
}

Scene::~Scene() {
	if( m_enabled[SCENE_BASE_UNLOAD] ) base_unload();
	unload();
	delete [] m_enabled;
}

void Scene::enable_defaults() {
	for( unsigned int i = 0; i < SCENE_ENABLE_LEN; i++ )
	  m_enabled[i] = true;
}

//----------------- run

void Scene::base_load() {
	if( m_enabled[SCENE_RENDERBUFFER] ) m_pRenderbuffer = new Renderbuffer();
	if( m_enabled[SCENE_CAMERA] ) m_pCamera = new Camera();
}

void Scene::base_unload() {
	SAFE_DELETE( m_pRenderbuffer );
	SAFE_DELETE( m_pCamera );
}

void Scene::load() {}
void Scene::unload() {}

void Scene::base_reshape() {
	if( m_enabled[SCENE_RENDERBUFFER] && m_pRenderbuffer != nullptr ) m_pRenderbuffer->reshape();
	if( m_enabled[SCENE_CAMERA] && m_pCamera != nullptr ) m_pCamera->reshape();
}

void Scene::reshape() {}

void Scene::base_update() {

}

void Scene::update() {
	filter_update();
}

void Scene::pre_render() {
	if( m_pRenderbuffer != nullptr ) m_pRenderbuffer->bind();
	else {
		glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
	}
}

void Scene::render() {  
	filter_render();
}

void Scene::post_render() {
	if( m_pRenderbuffer != nullptr ) m_pRenderbuffer->blit();
	else {
		glutSwapBuffers();
	}
}

//----------------- filter

void Scene::push_filter( Filter* f ) {
	if( f == nullptr ) {
		cerr << __FILE__ << ":" << __LINE__ << ": Not pushing NULL filter (" << f << ")." << endl;
		return;
	}
	m_filters.push_back( f );
}

void Scene::destroy_filters() {
	m_filters.clear();
}

void Scene::filter_update() {
	for( unsigned int i = 0; i < m_filters.size(); i++ ) {
		Filter* pF = m_filters[i];
		if( pF == nullptr ) continue;
		pF->update();
	}
}

void Scene::filter_render() {
	for( unsigned int i = 0; i < m_filters.size(); i++ ) {
		Filter* pF = m_filters[i];
		if( pF == nullptr ) continue;
		pF->render();
	}
}

//----------------- set

Scene* Scene::name( string s ) { m_name = s; return this; }
Scene* Scene::renderbuffer( Renderbuffer* pR ) {
	SAFE_DELETE( m_pRenderbuffer );
	m_pRenderbuffer = pR;
	return this;
}
Scene* Scene::camera( Camera* pC ) { m_pCamera = pC; return this; }
Scene* Scene::enable( unsigned int key, bool val ) { m_enabled[key] = val; return this; }
Scene* Scene::disable( unsigned int key, bool val ) { m_enabled[key] = val; return this; }

//----------------- get

string Scene::name() { return m_name; }
Renderbuffer* Scene::renderbuffer() { return m_pRenderbuffer; }
Camera* Scene::camera() { return m_pCamera; }
bool Scene::enabled( unsigned int key ) { return m_enabled[key]; }


} //jengine
