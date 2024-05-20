#version 450 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec3 out_normal;
out vec4 out_color;
out vec2 out_texCoord;

uniform mat4 camMatrix;
uniform met4 models[10];

void main()
{
	mat4 model = models[gl_InstanceID];
	gl_Position = camMatrix * model * vec4(pos, 1.0f);
	out_texCoord = texCoord;
	out_normal = mat3(transpose(inverse(model))) * normal;
}