/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > shape.cc
*******************************************************/
#include "jengine.h"
namespace jengine {

///////////////////////////////////////////////// FloorPlane

FloorPlane::FloorPlane( float w, float l ) {
	m_width = w;
	m_length = l;

	MESH_SETUP* s = new MESH_SETUP;
	s->draw = MESH_DRAW_ELEMENT;
	s->shape = MESH_SHAPE_TRIANGLE_STRIP;
	m_pMesh = new Mesh( s );
	vec vlist[4] = {
		vec( w/-2.0f, 0, l/-2.0f ),
		vec( w/2.0f, 0, l/-2.0f ),
		vec( w/2.0f, 0, l/2.0f ),
		vec( w/-2.0f, 0, l/2.0f )
	};
	m_pMesh->add_vertices( vlist, 4 );
	unsigned short ilist[6] = { 0, 3, 1, 2 };
	m_pMesh->add_indices( ilist, 4 );
	m_pMesh->build();
}

FloorPlane::~FloorPlane() {
	SAFE_DELETE( m_pMesh );
}

//----------------- run

void FloorPlane::render() {
	Entity::bind_model_mat();
	m_pMesh->render();
}

//----------------- get

float FloorPlane::width() { return m_width; }
float FloorPlane::length() { return m_length; }

} //jengine
