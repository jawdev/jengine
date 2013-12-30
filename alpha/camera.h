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
	void map_input( InputMap* = nullptr );
	void clear_input_map();

	// entity
	void attach_entity( Entity*, vec t = vec(), vec r = vec() );
	void clear_entity();

	// run
	void update();

	InputMap* m_pInputMap;
	Entity* m_pEntity;
	vec m_entityOffsetT;
	vec m_entityOffsetR;
};


} //jengine
#endif //__JENGINE_CAMERA_H__
