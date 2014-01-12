#version 330 core

uniform mat4 m4_camera;
uniform mat4 m4_model;
uniform vec4 v4_color = vec4( 1, 1, 1, 1 );

layout (location=0) in vec4 position;

out vec4 vs_fs_color;

void main( void ) {
	vs_fs_color = v4_color;
	gl_Position = m4_camera*m4_model*position;
}
