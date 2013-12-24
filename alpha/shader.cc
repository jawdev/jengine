/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > shader.cc
*******************************************************/
#include "jengine.h"
namespace jengine {

///////////////////////////////////////////////// Shader

Shader::Shader( string path, GLenum type ) {
	m_path = path;
	m_type = type;

	m_id = glCreateShader( m_type );
	const char* source = TOOL::file_get_contents( m_path.c_str(), true );
	glShaderSource( m_id, 1, &source, nullptr );
	glCompileShader( m_id );
	GLint compiled;
	glGetShaderiv( m_id, GL_COMPILE_STATUS, &compiled );
	if( !compiled ) {
		GLsizei len;
		glGetShaderiv( m_id, GL_INFO_LOG_LENGTH, &len );
		GLchar* log = new GLchar[len+1];
		glGetShaderInfoLog( m_id, len, &len, log );
		cerr << __FILE__ << ":" << __LINE__ << ": Shader could not be compiled (" << m_path << ")." << endl;
		cerr << log << endl;
		delete [] log;
		exit( 1 );
	}
}

Shader::~Shader() {

}

//----------------- get

string Shader::path() { return m_path; }
GLuint Shader::opengl_id() { return m_id; }
GLenum Shader::opengl_type() { return m_type; }

///////////////////////////////////////////////// ShaderProgram

ShaderProgram::ShaderProgram() {
	m_shaders[SHADER_COUNT] = { nullptr };
	m_id = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
	for( unsigned int i = 0; i < SHADER_COUNT; i++ ) {
		if( m_shaders[i] != nullptr ) delete m_shaders[i];
	}
	delete * m_shaders;
}

//----------------- run

void ShaderProgram::link() {
	glLinkProgram( m_id );
	GLint linked;
	glGetProgramiv( m_id, GL_LINK_STATUS, &linked );
	if( !linked ) {
		GLsizei len;
		glGetProgramiv( m_id, GL_INFO_LOG_LENGTH, &len );
		GLchar* log = new GLchar[len+1];
		glGetProgramInfoLog( m_id, len, &len, log );
		cerr << __FILE__ << ":" << __LINE__ << ": Shaders could not be linked." << endl;
		cerr << log << endl;
		delete [] log;
		exit( 1 );
	}
}

void ShaderProgram::use() {
	glUseProgram( m_id );
}

//----------------- load

void ShaderProgram::add_shader( GLenum type, string path ) {
	unsigned int i = type_map( type );
	m_shaders[i] = new Shader( path, type );
	glAttachShader( m_id, m_shaders[i]->opengl_id() );
}

void ShaderProgram::add_shader( Shader* pS ) {
	m_shaders[type_map( pS->opengl_type() )] = pS;
	glAttachShader( m_id, pS->opengl_id() );
}

//----------------- get

GLuint ShaderProgram::opengl_id() { return m_id; }
GLint ShaderProgram::uloc( string label ) { return glGetUniformLocation( m_id, label.c_str() ); }

//----------------- helpers

unsigned int ShaderProgram::type_map( GLenum type ) {
	switch( type ) {
		case GL_VERTEX_SHADER: return 0;
		case GL_FRAGMENT_SHADER: return 1;
		default: return 666;
	}
}

} //jengine
