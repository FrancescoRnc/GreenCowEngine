#pragma once
#include "../Engine/GreenCowEngine.h"

namespace OpenGL
{
	class Pipeline : public Engine::GPUPipeline
	{
		ProgramMap _registeredPrograms{};
		GLuint _defaultProgram{ 0 };
		std::vector<class Mesh*> meshes{};
		std::vector<struct MeshInstanceProfile> meshInstances{};


	public:
		Pipeline() {}

		COPY_MOVE_DELETE(Pipeline)

		// Inherited via GPUPipeline
		void CreateProgram(std::string programName, std::vector<std::string> files, bool useAsDefault = false) override;
		void Draw() override;
		// - - - -

		void InjectMeshes(std::vector<Mesh*> inMeshes);
		GLuint DefaultProgram() const;
		GLuint GetProgram(const std::string name) const;
		void UseDefaultProgram() const;
		void UseProgram(GLuint program) const;


	private:
		//GLuint _getVertexShaderFromSource(std::string shaderFilename);
		//GLuint _getFragmentShaderFromSource(std::string shaderFilename);
		GLuint _getShaderFromSource(GLenum shaderType, std::string shaderFilename);
		void _linkShadersToProgram(GLuint program, const std::vector<GLuint>& shaders);
		void _detachShadersFromProgram(const GLuint program, const std::vector<GLuint>& shaders);
		void _deleteShaders(const std::vector<GLuint>& shaders);
	};

	
}