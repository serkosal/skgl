#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;
//layout (location = 2) in vec2 aTexCoord;

out vec3 Normal;
out vec3 FragPos;
//out vec2 TexCoord;

uniform mat4 model, view, proj;

void main()
{
	gl_Position = proj * view * model * vec4(aPos, 1.0);

	// normal matrix should be calculated on CPU due the performance issues
	Normal = mat3(transpose(inverse(model))) * aNor;
	FragPos = vec3(model * vec4(aPos, 1.0));

	//TexCoord = aTexCoord;
}