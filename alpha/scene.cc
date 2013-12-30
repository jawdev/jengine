/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > scene.cc
*******************************************************/
#include "jengine.h"
namespace jengine {

///////////////////////////////////////////////// Scene

Scene::Scene( string name ) {
	m_name = name;
	m_pCamera = nullptr;
}

Scene::~Scene() {
	base_unload();
	unload();
}

//----------------- run

void Scene::base_load() {
	m_pCamera = new Camera();
	m_pRenderbuffer = new Renderbuffer();
	load();
}

void Scene::base_unload() {
	SAFE_DELETE( m_pCamera );
	SAFE_DELETE( m_pRenderbuffer );
}

void Scene::load() {}
void Scene::unload() {}
void Scene::reshape() {}

void Scene::update() {
	filter_update();
}

void Scene::render() {  
	m_pRenderbuffer->use();
	filter_render();
	m_pRenderbuffer->blit();
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
Scene* Scene::camera( Camera* pC ) { m_pCamera = pC; return this; }
Scene* Scene::renderbuffer( Renderbuffer* pR ) { m_pRenderbuffer = pR; return this; }

//----------------- get

string Scene::name() { return m_name; }
Camera* Scene::camera() { return m_pCamera; }
Renderbuffer* Scene::renderbuffer() { return m_pRenderbuffer; }


} //jengine
