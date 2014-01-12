/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > render.h
*******************************************************/
#ifndef __JENGINE_RENDER_H__
#define __JENGINE_RENDER_H__
namespace jengine {

///////////////////////////////////////////////// RenderBuffer

class Renderbuffer {
public:
	static const unsigned int COLOR_BUFFER = 0;
	static const unsigned int DEPTH_BUFFER = 1;
	static const unsigned int NUM_BUFFERS = 2;

public:
	Renderbuffer();
	~Renderbuffer();

	// manage
	void reshape( unsigned int w = 0, unsigned int h = 0 );
	void bind();
	void blit( unsigned int fid = 0 );

	// set
	Renderbuffer* clear_color( vec );

	// get
	unsigned int width();
	unsigned int height();
	vec clear_color();
	GLuint gl_framebuffer();
	GLuint gl_renderbuffer( unsigned int id );

private:
	unsigned int m_width;
	unsigned int m_height;
	vec m_clearColor;
	GLuint m_framebuffer;
	GLuint* m_renderbuffers;
};


} //jengine
#endif //__JENGINE_RENDER_H__
