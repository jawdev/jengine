/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > scene.cc
*******************************************************/
#include "jengine.h"
namespace jengine {

///////////////////////////////////////////////// Scene

Scene::Scene( string name ) {
	m_name = name;
}

Scene::~Scene() { unload(); }

//----------------- run

void Scene::load() {}
void Scene::unload() {}
void Scene::reshape() {}
void Scene::display() {}

void Scene::update_filters() {
	for( unsigned int i = 0; i < m_filters.size(); i++ ) {
		Filter* pF = m_filters[i];
		if( pF == nullptr ) continue;
		pF->update();
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

//----------------- set

Scene* Scene::name( string s ) { m_name = s; return this; }

//----------------- get

string Scene::name() { return m_name; }


} //jengine
