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

	// set
	Entity* position( vec v );
	Entity* rotation( vec v );
	Entity* scale( vec v );
	Entity* velocity( vec v );
	Entity* spin( vec v );
	Entity* morph( vec v );

	// get
	vec position();
	vec rotation();
	vec scale();
	vec velocity();
	vec spin();
	vec morph();
	mat transform();
	mat transform_world();
private:
	vec m_position;
	vec m_rotation;
	vec m_scale;
	vec m_velocity;
	vec m_spin;
	vec m_morph;
};


} //jengine
#endif //__JENGINE_ENTITY_H__
