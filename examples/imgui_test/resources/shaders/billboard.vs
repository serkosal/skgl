#version 330

layout (location = 0) in vec3 v_pos;
//layout (location = 1) in vec3 a_nor;
layout (location = 2) in vec2 v_tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 f_tex;

void main()
{
	gl_Position = proj * view * model * vec4(v_pos, 1.0);
	f_tex = v_tex;
}