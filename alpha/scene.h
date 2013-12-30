/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > scene.h
*******************************************************/
#ifndef __JENGINE_SCENE_H__
#define __JENGINE_SCENE_H__
namespace jengine {

///////////////////////////////////////////////// Scene

class Scene {
public:
	Scene( string name );
	~Scene();

	// run
	void base_load();
	void base_unload();
	virtual void load();
	virtual void unload();
	virtual void reshape();
	virtual void update();
	virtual void render();

	// filter
	void push_filter( Filter* f );
	void destroy_filters();
	void filter_update();
	void filter_render();

	// set
	Scene* name( string s );
	Scene* camera( Camera* );
	Scene* renderbuffer( Renderbuffer* );

	// get
	string name();
	Camera* camera();
	Renderbuffer* renderbuffer();
protected:
	string m_name;
	vector< Filter* > m_filters;
	Camera* m_pCamera;
	Renderbuffer* m_pRenderbuffer;
};


} //jengine
#endif //__JENGINE_SCENE_H__
