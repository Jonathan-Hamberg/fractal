#version 330 core

in vec2 tex_coord;

out vec4 color;

uniform sampler2D textureID;

void main()
{
    color = texture(textureID, tex_coord);
}
