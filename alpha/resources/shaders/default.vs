#version 330 core

uniform mat4 m4_camera;
uniform mat4 m4_model;

layout (location=0) in vec4 position;
//layout (location=1) in vec4 color;

out vec4 vs_fs_color;

mat4 M = mat4(	1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 1, 1 );

void main( void ) {
	vs_fs_color = vec4( 1, 0, 0, 1 );
	gl_Position = m4_camera*m4_model*position;
}
