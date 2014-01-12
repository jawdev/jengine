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
	FloorPlane( float w, float l );
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


} //jengine
#endif //__JENGINE_SHAPE_H__
