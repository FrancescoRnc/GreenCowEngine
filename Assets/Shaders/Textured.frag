#version 450 core

in vec4 out_color;
in vec2 out_texCoord;

out vec4 color;

uniform sampler2D Texture;

void main()
{
	//color = texture(Texture, out_texCoord) * vec4(1.0f);
	color = vec4(1.0f);
}