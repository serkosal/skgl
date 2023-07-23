#version 330

in vec2 f_tex;

uniform sampler2D billboard_texture;

out vec4 FragColor;

void main()
{
    FragColor = texture(billboard_texture, f_tex);
}