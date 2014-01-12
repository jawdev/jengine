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
	m_projType = PROJ_PERSPECTIVE;
	reshape();
}

Camera::~Camera() {
	if( m_pInputMap != nullptr ) delete m_pInputMap;
}

//----------------- input mapping

Camera* Camera::map_input( InputMap* pIM ) {
	if( m_pInputMap != nullptr ) delete m_pInputMap;
	if( pIM == nullptr ) m_pInputMap = new InputMap();
	else m_pInputMap = pIM;
	return this;
}

void Camera::clear_input_map() {
	if( m_pInputMap != nullptr ) delete m_pInputMap;
}

//----------------- entity

Camera* Camera::attach_entity( Entity* pE, vec t, vec r ) {
	m_pEntity = pE;
	m_entityOffsetT = t;
	m_entityOffsetR = r;
	return this;
}

void Camera::clear_entity() {
	m_pEntity = nullptr;
}

//----------------- projection

void Camera::project( unsigned int t ) {
	float aspect = (float)GLOBAL::window_width/(float)GLOBAL::window_height;
	m_projType = t;
	switch( t ) {
	case PROJ_NONE:
		m_projection.identity();
		break;
	case PROJ_PERSPECTIVE:
		vmath::perspective( &m_projection, -aspect, aspect, -1, 1, 1, GLOBAL::render_distance );
		break;
	case PROJ_ORTHOGRAPHIC:
		vmath::orthographic( &m_projection, -aspect, aspect, -1, 1, 1, GLOBAL::render_distance );
		break;
	default:
		m_projType = -1;
		cerr << __FILE__ << ":" << __LINE__ << ": Undefined projection value (" << t << ")" << endl;
		break;
	}
	if( locked() ) finalize();
}

void Camera::reshape() {
	project( m_projType );
}

void Camera::finalize() {
	m_final = m_projection*transform();
}

//----------------- run

void Camera::on_lock() {
	Entity::gen_transform_world();
	finalize();
}

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
	} else if( !locked() ) {
		Entity::spatialize();
	}
}

void Camera::bind() {
	if( !Entity::locked() ) {
		Entity::gen_transform_world();
		finalize();
	}
	glUniformMatrix4fv( GLOBAL::shader_spec[ULOC_CAMERA_MAT], 1, GL_FALSE, m_final.glfloat_data() );
}

//----------------- set

Camera* Camera::mat_projection( mat m ) { m_projection = m; if( locked() ) finalize(); return this; }
Camera* Camera::mat_final( mat m ) { m_final = m; return this; }

//----------------- get

mat Camera::mat_projection() { return m_projection; }
mat Camera::mat_final() { return m_final; }

} //jengine
