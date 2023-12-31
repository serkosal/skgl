#version 330 core

layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec2 aNor;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model, view, proj;

void main()
{
	// gl_Position = vec4(aPos, 1.0);

	gl_Position = proj * view * model * vec4(aPos, 1.0);

	TexCoord = aTexCoord;
}