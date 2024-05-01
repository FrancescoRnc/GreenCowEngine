#pragma once
//#include "OpenGL4Api.h"
#include "../GreenCowEngine.h"

namespace GreenCow
{
	struct OpenGL4FileLoader
	{
		bool LoadModel(std::string filepath,
					   std::vector<Vertex>& out_vertices,
					   std::vector<GLint>& out_indices);

		GLuint LoadTexture(std::string filepath);
	};
}