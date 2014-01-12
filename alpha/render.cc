/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > render.cc
*******************************************************/
#include "jengine.h"
namespace jengine {

///////////////////////////////////////////////// Renderbuffer

Renderbuffer::Renderbuffer() {
	m_width = GLOBAL::window_width;
	m_height = GLOBAL::window_height;

	m_renderbuffers = new GLuint[NUM_BUFFERS];
	glGenRenderbuffers( NUM_BUFFERS, m_renderbuffers );
	glBindRenderbuffer( GL_RENDERBUFFER, m_renderbuffers[COLOR_BUFFER] );
	glRenderbufferStorage( GL_RENDERBUFFER, GL_RGBA, m_width, m_height );
	glBindRenderbuffer( GL_RENDERBUFFER, m_renderbuffers[DEPTH_BUFFER] );
	glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_width, m_height );
	
	glGenFramebuffers( 1, &m_framebuffer );
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, m_framebuffer );
	glFramebufferRenderbuffer( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_renderbuffers[COLOR_BUFFER] );
	glFramebufferRenderbuffer( GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_renderbuffers[DEPTH_BUFFER] );

	glEnable( GL_DEPTH_TEST );
}

Renderbuffer::~Renderbuffer() {
	delete [] m_renderbuffers;
}

//----------------- manage

void Renderbuffer::reshape( unsigned int w, unsigned int h ) {
	if( w == 0 && h == 0 ) {
		w = GLOBAL::window_width;
		h = GLOBAL::window_height;
	}
	m_width = w;
	m_height = h;

	glDeleteRenderbuffers( NUM_BUFFERS, m_renderbuffers );

	glGenRenderbuffers( NUM_BUFFERS, m_renderbuffers );
	glBindRenderbuffer( GL_RENDERBUFFER, m_renderbuffers[COLOR_BUFFER] );
	glRenderbufferStorage( GL_RENDERBUFFER, GL_RGBA, m_width, m_height );
	glBindRenderbuffer( GL_RENDERBUFFER, m_renderbuffers[DEPTH_BUFFER] );
	glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_width, m_height );
	
	glGenFramebuffers( 1, &m_framebuffer );
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, m_framebuffer );
	glFramebufferRenderbuffer( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_renderbuffers[COLOR_BUFFER] );
	glFramebufferRenderbuffer( GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_renderbuffers[DEPTH_BUFFER] );
	
}

void Renderbuffer::bind() {
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, m_framebuffer );
	glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
}

void Renderbuffer::blit( unsigned int fid ) {
	glBindFramebuffer( GL_READ_FRAMEBUFFER, m_framebuffer );
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, fid );
	glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
	glBlitFramebuffer( 0, 0, m_width-1, m_height-1, 0, 0, m_width-1, m_height-1, GL_COLOR_BUFFER_BIT, GL_NEAREST );
	glutSwapBuffers();
}

//----------------- get

unsigned int Renderbuffer::width() { return m_width; }
unsigned int Renderbuffer::height() { return m_height; }
GLuint Renderbuffer::gl_framebuffer() { return m_framebuffer; }
GLuint Renderbuffer::gl_renderbuffer( unsigned int id ) { return m_renderbuffers[id]; }

} //jengine
