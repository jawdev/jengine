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

///////////////////////////////////////////////// ShaderSpec

enum shader_uloc_t : unsigned int {
	ULOC_CAMERA_MAT,
	ULOC_MODEL_MAT,
	ULOC_BASE_COLOR,
	ULOC_LEN
};

struct ShaderSpec {
	ShaderSpec() {
		for( unsigned int i = 0; i < ULOC_LEN; i++ ) {
			uniform_locations[i] = -1;
		}
	}
	ShaderSpec& operator=( const ShaderSpec& s ) {
		if( this == &s ) return *this;
		for( unsigned int i = 0; i < ULOC_LEN; i++ ) {
			uniform_locations[i] = s.uniform_locations[i];
		}
		return *this;
	}
	inline GLint& operator[]( const unsigned int& i ) {
		return uniform_locations[i];
	}
	GLint uniform_locations[ULOC_LEN];
};

struct ShaderSpecRef {
	ShaderSpecRef() {
		uniform_names[ULOC_CAMERA_MAT] = "m4_camera";
		uniform_names[ULOC_MODEL_MAT] = "m4_model";
		uniform_names[ULOC_BASE_COLOR] = "v4_color";
	}
	string uniform_names[ULOC_LEN];
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
	ShaderProgram* add_shader( GLenum type, string path );
	ShaderProgram* add_shader( Shader* );
	ShaderProgram* spec( const ShaderSpec& );
	ShaderProgram* spec( const ShaderSpecRef& );

	// get
	bool linked();
	GLuint opengl_id();
	GLint uloc( string label );
	ShaderSpec* spec();
	
private:
	unsigned int type_map( GLenum type );

private:
	GLuint m_id;
	Shader* m_shaders[SHADER_COUNT];
	bool m_linked;
	ShaderSpec m_shaderSpec;
};

} //jengine
#endif //__JENGINE_SHADER_H__
