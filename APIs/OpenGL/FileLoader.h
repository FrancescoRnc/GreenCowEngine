#pragma once
//#include "Api.h"
#include "../GreenCowEngine.h"

namespace OpenGL
{
	struct FileLoader
	{
		bool LoadModel(std::string filepath,
					   std::vector<Engine::Vertex>& out_vertices,
					   std::vector<GLint>& out_indices);
		const int LoadModels(std::string directory);
		bool LoadScenes(std::string directory);

		GLuint LoadTexture(std::string filepath);
	};
}