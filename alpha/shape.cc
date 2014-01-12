/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > shape.cc
*******************************************************/
#include "jengine.h"
namespace jengine {

///////////////////////////////////////////////// FloorPlane

FloorPlane::FloorPlane( float w, float l, vec col ) {
	m_width = w;
	m_length = l;

	MESH_SETUP* s = new MESH_SETUP;
	s->draw = MESH_DRAW_ELEMENT;
	s->shape = MESH_SHAPE_TRIANGLE_STRIP;
	s->color = col;
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

///////////////////////////////////////////////// Box

Box::Box( float s, vec col ) {
	m_width = m_length = m_height = s;
	create_mesh( col );
}

Box::Box( float w, float l, float h, vec col ) {
	m_width = w;
	m_length = l;
	m_height = h;
	create_mesh( col );
}

Box::~Box() {
	SAFE_DELETE( m_pMesh );
}

void Box::create_mesh( vec col ) {
	MESH_SETUP* s = new MESH_SETUP;
	s->draw = MESH_DRAW_ELEMENT;
	s->shape = MESH_SHAPE_TRIANGLE_STRIP;
	s->color = col;
	s->primitive_restart_index = 0xff;
	m_pMesh = new Mesh( s );
	vec vlist[8] = {
		vec( m_width/-2.0f, m_height/2.0f, m_length/-2.0f ),	// 0
		vec( m_width/2.0f, m_height/2.0f, m_length/-2.0f ),	// 1
		vec( m_width/2.0f, m_height/2.0f, m_length/2.0f ),	// 2
		vec( m_width/-2.0f, m_height/2.0f, m_length/2.0f ),	// 3

		vec( m_width/-2.0f, m_height/-2.0f, m_length/-2.0f ),	// 4
		vec( m_width/2.0f, m_height/-2.0f, m_length/-2.0f ),	// 5
		vec( m_width/2.0f, m_height/-2.0f, m_length/2.0f ),	// 6
		vec( m_width/-2.0f, m_height/-2.0f, m_length/2.0f ),	// 7
	};
	m_pMesh->add_vertices( vlist, 8 );
	unsigned short ilist[17] = {
		1, 0, 2, 3, 6, 7, 5, 4,
		0xff,
		2, 6, 1, 5, 0, 4, 3, 7
	};
	m_pMesh->add_indices( ilist, 17 );
	m_pMesh->build();
}

//----------------- run

void Box::render() {
	Entity::bind_model_mat();
	m_pMesh->render();
}

//----------------- get

float Box::size() { return m_width; }
float Box::width() { return m_width; }
float Box::length() { return m_length; }
float Box::height() { return m_height; }

} //jengine
