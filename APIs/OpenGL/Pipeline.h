#pragma once
#include "../GreenCowEngine.h"

namespace OpenGL
{
	class Pipeline : public Engine::GPUPipeline
	{
		public:

		// Inherited via GPUPipeline
		void CreateProgram(std::string shaders_name) override;
		void Draw() override;
		// - - - -

		std::vector<Vertex> TotalVertices = {};
		std::vector<GLint> TotalIndices = {};

		GLuint Program = 0;
	};
}