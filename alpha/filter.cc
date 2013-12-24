/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > filter.cc
*******************************************************/
#include "jengine.h"
namespace jengine {

///////////////////////////////////////////////// Filter

Filter::Filter() {
	m_pShaderProgram = nullptr;
}

Filter::~Filter() {
	if( m_pShaderProgram != nullptr ) delete m_pShaderProgram;
}

//----------------- run

void Filter::update() {
	if( m_pShaderProgram != nullptr ) {
		ShaderProgram* lastShader = GLOBAL::shader_program;
		GLOBAL::shader_program = m_pShaderProgram;
		m_pShaderProgram->use();
		if( lastShader != nullptr ) lastShader->use();
		GLOBAL::shader_program = lastShader;
	}
	for( unsigned int i = 0; i < m_entities.size(); i++ ) {
		Entity* pE = m_entities[i];
		if( pE == nullptr ) continue;
		pE->update();
	}
}

//----------------- set

Filter* Filter::shader_program( ShaderProgram* pS ) { m_pShaderProgram = pS; return this; }

//----------------- get

vector< Entity* >* Filter::entities() { return &m_entities; }
ShaderProgram* Filter::shader_program() { return m_pShaderProgram; }

} //jengine
