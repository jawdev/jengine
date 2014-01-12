/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > scene.h
*******************************************************/
#ifndef __JENGINE_SCENE_H__
#define __JENGINE_SCENE_H__
namespace jengine {

///////////////////////////////////////////////// Scene

enum scene_enable_t : unsigned int {
	SCENE_BASE_LOAD,
	SCENE_BASE_UNLOAD,
	SCENE_CAMERA,
	SCENE_BASE_RESHAPE,
	SCENE_BASE_UPDATE,
	SCENE_RENDERBUFFER,
	SCENE_PRE_RENDER,
	SCENE_POST_RENDER,
	SCENE_ENABLE_LEN
};

class Scene {
public:
	Scene( string name );
	~Scene();
	void enable_defaults();

	// run
	void base_load();
	void base_unload();
	virtual void load();
	virtual void unload();
	void base_reshape();
	virtual void reshape();
	void base_update();
	virtual void update();
	void pre_render();
	virtual void render();
	void post_render();

	// filter
	void push_filter( Filter* f );
	void destroy_filters();
	void filter_update();
	void filter_render();

	// set
	Scene* name( string s );
	Scene* renderbuffer( Renderbuffer* );
	Scene* camera( Camera* );
	Scene* enable( unsigned int, bool=true );
	Scene* disable( unsigned int, bool=false );

	// get
	string name();
	Renderbuffer* renderbuffer();
	Camera* camera();
	bool enabled( unsigned int );
private:
	string m_name;
	bool* m_enabled;
	Renderbuffer* m_pRenderbuffer;
	vector< Filter* > m_filters;
	Camera* m_pCamera;
};


} //jengine
#endif //__JENGINE_SCENE_H__
