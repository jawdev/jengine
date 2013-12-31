/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > entity.h
*******************************************************/
#ifndef __JENGINE_ENTITY_H__
#define __JENGINE_ENTITY_H__
namespace jengine {

///////////////////////////////////////////////// Entity

class Entity {
public:
	Entity();
	virtual ~Entity();

	// run
	virtual void update();
	void spatialize();
	virtual void render();

	// hooks
	virtual void on_lock();
	virtual void on_unlock();

	// set
	Entity* lock( bool = true );
	Entity* position( vec );
	Entity* rotation( vec );
	Entity* scale( vec );
	Entity* velocity( vec );
	Entity* spin( vec );
	Entity* morph( vec );
	Entity* look_at( vec );

	// get
	bool locked();
	vec position();
	vec rotation();
	vec scale();
	vec velocity();
	vec spin();
	vec morph();
	mat transform();
	mat gen_transform();
	mat gen_transform_world();
private:
	bool m_locked;
	vec m_position;
	vec m_rotation;
	vec m_scale;
	vec m_velocity;
	vec m_spin;
	vec m_morph;
	mat m_transform;
};


} //jengine
#endif //__JENGINE_ENTITY_H__
