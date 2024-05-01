#pragma once
#include "../GreenCowEngine.h"

namespace GreenCow
{
	class OpenGL4Pipeline : public GPUPipeline
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