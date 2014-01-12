/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > shape.h
*******************************************************/
#ifndef __JENGINE_SHAPE_H__
#define __JENGINE_SHAPE_H__
namespace jengine {

///////////////////////////////////////////////// FloorPlane

class FloorPlane : public Entity {
public:
	FloorPlane( float w, float l, vec col = vec( 1, 1, 1, 1 ) );
	~FloorPlane();

	// run
	void render();

	// get
	float width();
	float length();
private:
	float m_width;
	float m_length;
	Mesh* m_pMesh;
};

///////////////////////////////////////////////// Box

class Box : public Entity {
public:
	Box( float s=1.0f, vec col = vec( 1, 1, 1, 1 ) );
	Box( float w, float l, float h, vec col = vec( 1, 1, 1, 1 ) );
	~Box();

	// run
	void render();

	// get
	float size();
	float width();
	float length();
	float height();
private:
	void create_mesh( vec col );

	float m_width;
	float m_length;
	float m_height;
	Mesh* m_pMesh;
};


} //jengine
#endif //__JENGINE_SHAPE_H__
