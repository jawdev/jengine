/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > mesh.h
*******************************************************/
#ifndef __JENGINE_MESH_H__
#define __JENGINE_MESH_H__
namespace jengine {

///////////////////////////////////////////////// MESH_SETUP

enum mesh_draw_t : unsigned int { MESH_DRAW_ARRAY, MESH_DRAW_ELEMENT, mesh_draw_t_len };
enum mesh_shape_t : unsigned int { MESH_SHAPE_POINTS, MESH_SHAPE_LINES, MESH_SHAPE_LINE_STRIP, MESH_SHAPE_LINE_LOOP, MESH_SHAPE_TRIANGLES, MESH_SHAPE_TRIANGLE_STRIP, MESH_SHAPE_TRIANGLE_FAN, mesh_shape_t_len };

struct MESH_SETUP {
	MESH_SETUP() {
		draw = MESH_DRAW_ARRAY;
		shape = MESH_SHAPE_TRIANGLES;
		primitive_restart_index = 0;
		color = vec( 1, 1, 1, 1 );
	}
	mesh_draw_t draw;
	mesh_shape_t shape;
	vec color;
	unsigned int primitive_restart_index;
};

static const GLuint MESH_SHAPE_MAP[mesh_shape_t_len] = {
	GL_POINTS,
	GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP,
	GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN
};

///////////////////////////////////////////////// Mesh

class Mesh {
public:
	Mesh( MESH_SETUP* pS = nullptr );
	~Mesh();

	// draw
	Mesh* add_vertex( vec );
	Mesh* add_vertices( vec*, unsigned int count );
	Mesh* add_index( unsigned short );
	Mesh* add_indices( unsigned short*, unsigned int cout );
	
	// run
	void build();
	void render();

private:
	static const unsigned int VERTEX_BUFFER = 0;
	static const unsigned int ELEMENT_BUFFER = 1;
private:
	MESH_SETUP* m_pSetup;
	bool m_isBuilt;
	vector< vec >* m_pV;
	vector< unsigned short >* m_pI;
	GLuint m_VA;
	GLuint* m_BUF;
	GLfloat* m_vertices;
	GLushort* m_indices;
	unsigned int m_countV;
	unsigned int m_countI;
	unsigned int m_vDataLen;
	unsigned int m_iDataLen;
};


} //jengine
#endif //__JENGINE_MESH_H__
