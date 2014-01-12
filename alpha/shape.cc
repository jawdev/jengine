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

	glGenVertexArrays( 1, &m_VA );
	glBindVertexArray( m_VA );

	vertices* vlist = new vertices;
	vlist->add( w/-2.0f, 0, l/-2.0f );
	vlist->add( w/2.0f, 0, l/-2.0f );
	vlist->add( w/2.0f, 0, l/2.0f );
	vlist->add( w/-2.0f, 0, l/2.0f );
	m_vertices = vlist->glfloat_data();

	indices* ilist = new indices;
	ilist->add( 3, 1, 0 );
	ilist->add( 3, 2, 1 );
	m_indices = ilist->glushort_data();

	glGenBuffers( 1, &m_EB );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_EB );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, ilist->glushort_size(), m_indices, GL_STATIC_DRAW );
	glGenBuffers( 1, &m_VB );
	glBindBuffer( GL_ARRAY_BUFFER, m_VB );
	glBufferData( GL_ARRAY_BUFFER, vlist->glfloat_size(), m_vertices, GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray( 0 );

	delete vlist;
	delete ilist;
}

FloorPlane::~FloorPlane() {
	SAFE_DELETE_ARR( m_indices );
	SAFE_DELETE_ARR( m_vertices );
}

//----------------- run

void FloorPlane::render() {
	glDisable( GL_CULL_FACE );
	glUniformMatrix4fv( GLOBAL::shader_spec[ULOC_MODEL_MAT], 1, GL_FALSE, Entity::gen_transform().glfloat_data() );
	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL );
}

//----------------- get

float FloorPlane::width() { return m_width; }
float FloorPlane::length() { return m_length; }

} //jengine
