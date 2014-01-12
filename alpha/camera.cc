/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > camera.cc
*******************************************************/
#include "jengine.h"
namespace jengine {

///////////////////////////////////////////////// InputMap

InputMap::InputMap() {
	m_tmult = m_rmult = 1.0f;
	m_useDelta = true;
}

InputMap::~InputMap() {

}

//----------------- run

void InputMap::update( Entity* pE ) {
	m_translation.x = m_tmult.x*( ( INPUT::key['a']?-1:0 )+( INPUT::key['d']?1:0 ) );
	m_translation.y = m_tmult.y*( ( INPUT::special[112]?1:0 )+( INPUT::special[114]?-1:0 ) );
	m_translation.z = m_tmult.z*( ( INPUT::key['w']?-1:0 )+( INPUT::key['s']?1:0 ) );

	//float dy = INPUT::mouse_y-INPUT::last_mouse_y;
	if( INPUT::mouse_moved ) {
		m_rotation.y = -1.0f*m_rmult.y*INPUT::mouse_dx;
		m_rotation.x = -1.0f*m_rmult.x*INPUT::mouse_dy;
		INPUT::poll_mouse();
	}

	if( m_useDelta ) {
		m_translation *= GLOBAL::stopwatch.delta;
		m_rotation *= GLOBAL::stopwatch.delta;
	}

	if( pE == nullptr ) return;

	if( pE->rotation().y != 0 ) {
		vmath::mat_rotation_y( &m_matTemp, pE->rotation().y );
		m_translation *= m_matTemp;
	}
	pE->rotation( pE->rotation()+m_rotation );
	pE->position( pE->position()+m_translation );
}

//----------------- set

InputMap* InputMap::multiply_transform( vec t, vec r ) {
	multiply_translation( t );
	multiply_rotation( r );
	return this;
}
InputMap* InputMap::multiply_transform( float t, float r ) {
	multiply_translation( t );
	multiply_rotation( r );
	return this;
}
InputMap* InputMap::multiply_translation( vec t ) { m_tmult = t; return this; }
InputMap* InputMap::multiply_translation( float t ) { m_tmult = vec( t, t, t ); return this; }
InputMap* InputMap::multiply_rotation( vec r ) { m_rmult = r; return this; }
InputMap* InputMap::multiply_rotation( float r ) { m_rmult = vec( r, r ); return this; }
InputMap* InputMap::enable_delta( bool b ) { m_useDelta = b; return this; }

//----------------- get

vec InputMap::translation() { return m_translation; }
vec InputMap::rotation() { return m_rotation; }

///////////////////////////////////////////////// Camera

Camera::Camera() {
	m_pInputMap = nullptr;
	m_pEntity = nullptr;
	m_projType = PROJ_PERSPECTIVE;
	SETUP* pS = (SETUP*)GLOBAL::setup_instance;
	m_renderDistance = new float[2];
	m_renderDistance[0] = pS->default_render_distance_near;
	m_renderDistance[1] = pS->default_render_distance_far;
	reshape();
}

Camera::~Camera() {
	if( m_pInputMap != nullptr ) delete m_pInputMap;
	SAFE_DELETE_ARR( m_renderDistance );
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
		vmath::perspective( &m_projection, -aspect, aspect, -1, 1, m_renderDistance[0], m_renderDistance[1] );
		break;
	case PROJ_ORTHOGRAPHIC:
		vmath::orthographic( &m_projection, -aspect, aspect, -1, 1, m_renderDistance[0], m_renderDistance[1] );
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
		m_pInputMap->update( this );
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
Camera* Camera::render_distance( float n, float f ) {
	m_renderDistance[0] = n;
	m_renderDistance[1] = f;
	return this;
}
Camera* Camera::render_distance_near( float n ) { m_renderDistance[0] = n; return this; }
Camera* Camera::render_distance_far( float f ) { m_renderDistance[1] = f; return this; }

//----------------- get

mat Camera::mat_projection() { return m_projection; }
mat Camera::mat_final() { return m_final; }
float* Camera::render_distance() { return m_renderDistance; }
float Camera::render_distance_near() { return m_renderDistance[0]; }
float Camera::render_distance_far() { return m_renderDistance[1]; }

} //jengine
