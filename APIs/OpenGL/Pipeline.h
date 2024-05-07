#pragma once
#include "../GreenCowEngine.h"

namespace OpenGL
{
	class Pipeline : public Engine::GPUPipeline
	{
		Helpers::ProgramMap _registeredPrograms{};
		GLuint _defaultProgram;

		public:

		// Inherited via GPUPipeline
		void CreateProgram(std::string programName, std::vector<std::string> files, bool useAsDefault = false) override;
		void Draw() override;
		// - - - -

		std::vector<Vertex> TotalVertices = {};
		std::vector<GLint> TotalIndices = {};

		//GLuint Program = 0;
		inline GLuint DefaultProgram() const { return _defaultProgram; }

		inline void SerializePrograms() const
		{
			Helpers::SerializedDataRetriever::SerializePrograms(_registeredPrograms);
		}
	};

	
}