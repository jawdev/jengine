/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > filter.cc
*******************************************************/
#include "jengine.h"
namespace jengine {

///////////////////////////////////////////////// Filter

Filter::Filter() {
}

Filter::~Filter() {
}

//----------------- run

void Filter::update() {
	for( unsigned int i = 0; i < m_entities.size(); i++ ) {
		Entity* pE = m_entities[i];
		if( pE == nullptr ) continue;
		pE->update();
	}
}

void Filter::render() {
	for( unsigned int i = 0; i < m_entities.size(); i++ ) {
		Entity* pE = m_entities[i];
		if( pE == nullptr ) continue;
		pE->render();
	}
}

//----------------- get

vector< Entity* >* Filter::entities() { return &m_entities; }

} //jengine
