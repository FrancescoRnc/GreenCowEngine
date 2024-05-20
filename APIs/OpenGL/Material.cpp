#include "Material.h"


GLuint OpenGL::Material::GetProgram() const
{
	return UsedShader ? UsedShader->Program : program;
}

void OpenGL::Material::ApplyUniformMat4To(const char* uniformName, glm::mat4 value)
{
	GLint uniformId = glGetUniformLocation(program, uniformName);
	glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGL::Material::ApplyMat4Uniforms(const std::unordered_map<const char*, glm::mat4> uniforms)
{
	for (auto uniform : uniforms)
	{
		GLint uniformId = glGetUniformLocation(program, uniform.first);
		glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(uniform.second));
	}
}

void OpenGL::Material::ApplyTextures()
{
	for (auto texture : Textures)
	{
		// bind and use Texture
	}
}

