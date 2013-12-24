/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > shader.h
*******************************************************/
#ifndef __JENGINE_SHADER_H__
#define __JENGINE_SHADER_H__
namespace jengine {

///////////////////////////////////////////////// Shader

class Shader {
public:
	Shader( string path, GLenum type );
	~Shader();

	// get
	string path();
	GLuint opengl_id();
	GLenum opengl_type();

private:
	GLuint m_id;
	string m_path;
	GLenum m_type;
};

///////////////////////////////////////////////// ShaderProgram

class ShaderProgram {
public:
	static const unsigned int SHADER_COUNT = 2;
public:
	ShaderProgram();
	~ShaderProgram();

	// run
	void link();
	void use();

	// load
	void add_shader( GLenum type, string path );
	void add_shader( Shader* );

	// get
	GLuint opengl_id();
	GLint uloc( string label );
	
private:
	unsigned int type_map( GLenum type );

private:
	GLuint m_id;
	Shader* m_shaders[SHADER_COUNT];
};

} //jengine
#endif //__JENGINE_SHADER_H__
