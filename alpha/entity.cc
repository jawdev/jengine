/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > entity.cc
*******************************************************/
#include "jengine.h"
namespace jengine {

///////////////////////////////////////////////// Entity

Entity::Entity() {
}

Entity::~Entity() {

}

//----------------- run

void Entity::update() {
	spatialize();
}

void Entity::spatialize() {
	float dtime = TIMER::delta;
	m_position += m_velocity*dtime;
	m_rotation += m_spin*dtime;
	m_scale += m_morph*dtime;
}

void Entity::render() {

}



//----------------- set

Entity* Entity::position( vec v ) { m_position = v; return this; }
Entity* Entity::rotation( vec v ) { m_rotation = v; return this; }
Entity* Entity::scale( vec v ) { m_scale = v; return this; }
Entity* Entity::velocity( vec v ) { m_velocity = v; return this; }
Entity* Entity::spin( vec v ) { m_spin = v; return this; }
Entity* Entity::morph( vec v ) { m_morph = v; return this; }

//----------------- get

vec Entity::position() { return m_position; }
vec Entity::rotation() { return m_rotation; }
vec Entity::scale() { return m_scale; }
vec Entity::velocity() { return m_velocity; }
vec Entity::spin() { return m_spin; }
vec Entity::morph() { return m_morph; }

mat Entity::transform() {
	mat trans, rot;
	vmath::mat_translation( m_position, &trans );
	vmath::mat_rotation( m_rotation, &rot );
	return rot*trans;
}

mat Entity::transform_world() {
	mat trans, rot;
	vmath::mat_translation( -m_position, &trans );
	vmath::mat_rotation( m_rotation, &rot );
	return trans*rot;
}


} //jengine
