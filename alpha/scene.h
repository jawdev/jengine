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
	virtual void load();
	virtual void unload();
	virtual void reshape();
	virtual void display();
	void update_filters();

	// filter
	void push_filter( Filter* f );
	void destroy_filters();

	// set
	Scene* name( string s );

	// get
	string name();
protected:
	string m_name;
	vector< Filter* > m_filters;
};


} //jengine
#endif //__JENGINE_SCENE_H__
