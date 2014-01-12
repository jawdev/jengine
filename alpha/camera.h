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
	virtual void update( Entity* pE = nullptr );

	// set
	InputMap* multiply_transform( vec, vec );
	InputMap* multiply_transform( float, float );
	InputMap* multiply_translation( vec );
	InputMap* multiply_translation( float );
	InputMap* multiply_rotation( vec );
	InputMap* multiply_rotation( float );
	InputMap* enable_delta( bool=true );

	// get
	vec translation();
	vec rotation();
private:
	vec m_tmult;
	vec m_rmult;
	bool m_useDelta;
	vec m_translation;
	vec m_rotation;
	mat m_matTemp;
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
	Camera* render_distance( float, float );
	Camera* render_distance_near( float );
	Camera* render_distance_far( float );

	// get
	mat mat_projection();
	mat mat_final();
	float* render_distance();
	float render_distance_near();
	float render_distance_far();
private:
	InputMap* m_pInputMap;
	unsigned int m_projType;
	mat m_projection;
	mat m_final;
	Entity* m_pEntity;
	vec m_entityOffsetT;
	vec m_entityOffsetR;
	float* m_renderDistance;
};


} //jengine
#endif //__JENGINE_CAMERA_H__
