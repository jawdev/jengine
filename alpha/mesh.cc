/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > mesh.cc
*******************************************************/
#include "jengine.h"
namespace jengine {

///////////////////////////////////////////////// Mesh

Mesh::Mesh( MESH_SETUP* pS ) {
	if( pS == nullptr ) m_pSetup = new MESH_SETUP;
	else m_pSetup = pS;
	m_isBuilt = false;
	m_pV = new vector< vec >;
	m_pI = new vector< unsigned short >;
	m_countV = m_countI = m_vDataLen = m_iDataLen = 0;
}

Mesh::~Mesh() {
	SAFE_DELETE( m_pSetup );
	SAFE_DELETE( m_pV );
	SAFE_DELETE( m_pI );
	SAFE_DELETE_ARR( m_BUF );
}

//----------------- draw

Mesh* Mesh::add_vertex( vec v ) {
	if( m_isBuilt ) {
		cerr << __FILE__ << ":" << __LINE__ << ": Cannot add vertex " << v << " to built Mesh." << endl;
		return this;
	}
	m_pV->push_back( v );
	return this;
}

Mesh* Mesh::add_vertices( vec* v, unsigned int count ) {
	if( v == nullptr ) {
		cerr << __FILE__ << ":" << __LINE__ << ": Cannot add null vertices (" << v << ") to Mesh." << endl;
		return this;
	} else if( m_isBuilt ) {
		cerr << __FILE__ << ":" << __LINE__ << ": Cannot add " << count << " vertices (" << v << ") to built Mesh." << endl;
		return this;
	}
	for( unsigned int i = 0; i < count; i++ ) m_pV->push_back( v[i] );
	return this;
}

Mesh* Mesh::add_index( unsigned short i ) {
	if( m_isBuilt ) {
		cerr << __FILE__ << ":" << __LINE__ << ": Cannot add index " << i << " to built Mesh." << endl;
		return this;
	} else if( m_pSetup->draw != MESH_DRAW_ELEMENT ) {
		cerr << __FILE__ << ":" << __LINE__ << ": Cannot add index to Mesh where mesh_draw_t = MESH_DRAW_ARRAY, MESH_DRAW_ELEMENT required." << endl;
		return this;
	}
	m_pI->push_back( i );
	return this;
}

Mesh* Mesh::add_indices( unsigned short* i, unsigned int count ) {
	if( i == nullptr ) {
		cerr << __FILE__ << ":" << __LINE__ << ": Cannot add null indices (" << i << ") to Mesh." << endl;
		return this;
	} else if( m_isBuilt ) {
		cerr << __FILE__ << ":" << __LINE__ << ": Cannot add " << count << " indices (" << i << ") to built Mesh." << endl;
		return this;
	} else if( m_pSetup->draw != MESH_DRAW_ELEMENT ) {
		cerr << __FILE__ << ":" << __LINE__ << ": Cannot add index to Mesh where mesh_draw_t = MESH_DRAW_ARRAY, MESH_DRAW_ELEMENT required." << endl;
		return this;
	}
	for( unsigned int j = 0; j < count; j++ ) m_pI->push_back( i[j] );
	return this;
}

//----------------- Mesh

void Mesh::build() {
	if( m_isBuilt ) {
		cerr << __FILE__ << ":" << __LINE__ << ": Mesh has already been built." << endl;
		return;
	}

	glGenVertexArrays( 1, &m_VA );
	glBindVertexArray( m_VA );
	m_countV = m_pV->size();
	m_vDataLen = m_countV*4*sizeof( GLfloat );
	m_vertices = new GLfloat[m_countV*4];
	unsigned int j = 0;
	for( unsigned int i = 0; i < m_countV; i++ ) {
		vec pV = m_pV->at( i );
		m_vertices[j++] = (GLfloat)pV.x;
		m_vertices[j++] = (GLfloat)pV.y;
		m_vertices[j++] = (GLfloat)pV.z;
		m_vertices[j++] = (GLfloat)pV.w;
	}
	SAFE_DELETE( m_pV );

	if( m_pSetup->draw == MESH_DRAW_ELEMENT ) {
		m_countI = m_pI->size();
		m_iDataLen = m_countI*sizeof( GLushort );
		m_indices = new GLushort[m_countI];
		for( unsigned int i = 0; i < m_countI; i++ ) m_indices[i] = (GLushort)m_pI->at( i );
		SAFE_DELETE( m_pI );

		m_BUF = new GLuint[2];
		glGenBuffers( 2, m_BUF );
	} else {
		m_BUF = new GLuint[1];
		glGenBuffers( 1, m_BUF );
	}

	switch( m_pSetup->draw ) {
	case MESH_DRAW_ELEMENT:
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_BUF[ELEMENT_BUFFER] );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_iDataLen, m_indices, GL_STATIC_DRAW );
	case MESH_DRAW_ARRAY:
		glBindBuffer( GL_ARRAY_BUFFER, m_BUF[VERTEX_BUFFER] );
		glBufferData( GL_ARRAY_BUFFER, m_vDataLen, m_vertices, GL_STATIC_DRAW );
		break;
	default:
		cerr << __FILE__ << ":" << __LINE__ << ": Unknown Mesh drawing type (" << m_pSetup->draw << ")." << endl;
	}

	switch( m_pSetup->shape ) {
	case MESH_SHAPE_LINE_STRIP:
	case MESH_SHAPE_TRIANGLE_STRIP:
		if( m_pSetup->primitive_restart_index > 0 ) glPrimitiveRestartIndex( m_pSetup->primitive_restart_index );
	default:
		break;
	}
	
	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray( 0 );
	m_isBuilt = true;
}

void Mesh::render() {
	if( !m_isBuilt ) {
		cerr << __FILE__ << ":" << __LINE__ << ": Cannot render Mesh (" << this << ") before building." << endl;
		return;
	}
	if( m_pSetup->draw == MESH_DRAW_ELEMENT ) {
		glDrawElements( MESH_SHAPE_MAP[m_pSetup->shape], m_countI, GL_UNSIGNED_SHORT, NULL );
	} else {
		glDrawArrays( MESH_SHAPE_MAP[m_pSetup->shape], 0, m_countV );
	}
}

} //jengine
