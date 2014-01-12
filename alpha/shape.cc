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

	vertices* v = new jengine::vertices;
	v->add( w/-2.0f, 0, l/-2.0f );
	v->add( w/2.0f, 0, l/-2.0f );
	v->add( w/-2.0f, 0, l/2.0f );
	v->add( w/2.0f, 0, l/-2.0f );
	v->add( w/2.0f, 0, l/2.0f );
	v->add( w/-2.0f, 0, l/2.0f );
	m_vertices = v->glfloat_data();
	

	glGenBuffers( 1, &m_VB );
	glBindBuffer( GL_ARRAY_BUFFER, m_VB );
	glBufferData( GL_ARRAY_BUFFER, v->glfloat_size(), m_vertices, GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray( 0 );

	delete v;
}

FloorPlane::~FloorPlane() {
	SAFE_DELETE_ARR( m_vertices );
}

//----------------- run

void FloorPlane::render() {
	glDisable( GL_CULL_FACE );
	glUniformMatrix4fv( GLOBAL::shader_spec[ULOC_MODEL_MAT], 1, GL_FALSE, Entity::gen_transform().glfloat_data() );
	glBindVertexArray( m_VA );
	glDrawArrays( GL_TRIANGLES, 0, 6 );
}

//----------------- get

float FloorPlane::width() { return m_width; }
float FloorPlane::length() { return m_length; }

} //jengine
