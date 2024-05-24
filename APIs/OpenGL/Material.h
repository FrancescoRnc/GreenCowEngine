#pragma once
#include "../Engine/GreenCowEngine.h"
#include "Texture.h"
#include "Shader.h"

namespace OpenGL
{
	class Material
	{
		GLuint program = 0;

		public:
		Material(const GLuint defaulProgram) : UsedShader(nullptr), Textures({}), program(defaulProgram) {}
		Material(Shader* shader, std::vector<GLuint> textures) : UsedShader(shader), Textures(textures), program(shader->Program) {}

		Shader* UsedShader;
		std::vector<GLuint> Textures;

		GLuint GetProgram() const;

		void ApplyUniformMat4To(const char* uniformName, glm::mat4 value);
		void ApplyMat4Uniforms(const std::unordered_map<const char*, glm::mat4> uniforms);
		void ApplyTextures();
	};
}
