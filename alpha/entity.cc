/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > entity.cc
*******************************************************/
#include "jengine.h"
namespace jengine {

///////////////////////////////////////////////// Entity

Entity::Entity() {
	m_locked = false;
}

Entity::~Entity() {

}

//----------------- run

void Entity::update() {
	if( m_locked ) return;
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

//----------------- hooks

void Entity::on_lock() { transform(); }
void Entity::on_unlock() {}

//----------------- set

Entity* Entity::lock( bool b ) {
	m_locked = b;
	if( b ) on_lock();
	else on_unlock();
	return this;
}

Entity* Entity::position( vec v ) { m_position = v; return this; }
Entity* Entity::rotation( vec v ) { m_rotation = v; return this; }
Entity* Entity::scale( vec v ) { m_scale = v; return this; }
Entity* Entity::velocity( vec v ) { m_velocity = v; return this; }
Entity* Entity::spin( vec v ) { m_spin = v; return this; }
Entity* Entity::morph( vec v ) { m_morph = v; return this; }

Entity* Entity::look_at( vec v ) {
	float dx = v.x-m_position.x;
	float dy = v.y-m_position.y;
	float dz = v.z-m_position.z;
	float yang = atan2( dz, dx );
	float hyp = sqrt( dx*dx+dz*dz );
	m_rotation.y = yang;
	m_rotation.z = ( hyp==0?0:atan( dy/hyp ) );
	return this;
}

//----------------- get

bool Entity::locked() { return m_locked; }
vec Entity::position() { return m_position; }
vec Entity::rotation() { return m_rotation; }
vec Entity::scale() { return m_scale; }
vec Entity::velocity() { return m_velocity; }
vec Entity::spin() { return m_spin; }
vec Entity::morph() { return m_morph; }

mat Entity::transform() { return m_transform; }

mat Entity::gen_transform() {
	mat trans, rot;
	vmath::mat_translation( m_position, &trans );
	vmath::mat_rotation( m_rotation, &rot );
	m_transform = rot*trans;
	return m_transform;
}

mat Entity::gen_transform_world() {
	mat trans, rot;
	vmath::mat_translation( -m_position, &trans );
	vmath::mat_rotation( m_rotation, &rot );
	m_transform = trans*rot;
	return m_transform;
}


} //jengine
