/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > camera.h
*******************************************************/
#ifndef __JENGINE_CAMERA_H__
#define __JENGINE_CAMERA_H__
namespace jengine {

///////////////////////////////////////////////// InputMap

class InputMap {
public:
	InputMap();
	virtual ~InputMap();

	// run
	virtual void update();

	// get
	vec translation();
	vec rotation();
private:
	vec m_translation;
	vec m_rotation;
};

///////////////////////////////////////////////// Camera

class Camera : public Entity {
public:
	Camera();
	~Camera();

	// input mapping
	Camera* map_input( InputMap* = nullptr );
	void clear_input_map();

	// entity
	Camera* attach_entity( Entity*, vec t = vec(), vec r = vec() );
	void clear_entity();

	// projection
	Camera* load_projection( const mat& m );

	// run
	void on_lock();
	void update();
	void apply();

private:
	InputMap* m_pInputMap;
	mat m_projection;
	Entity* m_pEntity;
	vec m_entityOffsetT;
	vec m_entityOffsetR;
};


} //jengine
#endif //__JENGINE_CAMERA_H__
