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

enum camera_proj_t : unsigned int {
	PROJ_NONE,
	PROJ_PERSPECTIVE,
	PROJ_ORTHOGRAPHIC,
	PROJ_LEN
};

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
	void project( unsigned int t = PROJ_PERSPECTIVE );
	void reshape();
	void finalize();

	// run
	void on_lock();
	void update();
	void bind();

	// set
	Camera* mat_projection( mat );
	Camera* mat_final( mat );

	// get
	mat mat_projection();
	mat mat_final();
private:
	InputMap* m_pInputMap;
	unsigned int m_projType;
	mat m_projection;
	mat m_final;
	Entity* m_pEntity;
	vec m_entityOffsetT;
	vec m_entityOffsetR;
};


} //jengine
#endif //__JENGINE_CAMERA_H__
