/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > camera.cc
*******************************************************/
#include "jengine.h"
namespace jengine {

///////////////////////////////////////////////// InputMap

InputMap::InputMap() {

}

InputMap::~InputMap() {

}

//----------------- run

void InputMap::update() {

}

//----------------- get

vec InputMap::translation() { return m_translation; }
vec InputMap::rotation() { return m_rotation; }

///////////////////////////////////////////////// Camera

Camera::Camera() {
	m_pInputMap = nullptr;
	m_pEntity = nullptr;
}

Camera::~Camera() {
	if( m_pInputMap != nullptr ) delete m_pInputMap;
}

//----------------- input mapping

void Camera::map_input( InputMap* pIM ) {
	if( m_pInputMap != nullptr ) delete m_pInputMap;
	if( pIM == nullptr ) m_pInputMap = new InputMap();
	else m_pInputMap = pIM;
}

void Camera::clear_input_map() {
	if( m_pInputMap != nullptr ) delete m_pInputMap;
}

//----------------- entity

void Camera::attach_entity( Entity* pE, vec t, vec r ) {
	m_pEntity = pE;
	m_entityOffsetT = t;
	m_entityOffsetR = r;
}

void Camera::clear_entity() {
	m_pEntity = nullptr;
}

//----------------- run

void Camera::update() {
	if( m_pInputMap != nullptr ) {
		m_pInputMap->update();
		Entity::position( m_pInputMap->translation() );
		Entity::rotation( m_pInputMap->rotation() );
		if( m_pEntity != nullptr ) {
			m_pEntity->position( Entity::position()-m_entityOffsetT );
			m_pEntity->rotation( Entity::rotation()-m_entityOffsetR );
		}
	} else if( m_pEntity != nullptr ) {
		Entity::position( m_pEntity->position()+m_entityOffsetT );
		Entity::rotation( m_pEntity->rotation()+m_entityOffsetR );
	} else {
		Entity::spatialize();
	}
}

} //jengine
