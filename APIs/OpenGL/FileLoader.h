#pragma once
#include "../Engine/GreenCowEngine.h"
#include "Mesh.h"
#include "Texture.h"

namespace OpenGL
{
	struct FileLoader
	{
		static bool LoadMesh(std::string filename, MeshData& out_mesh);
		static bool LoadTexture(std::string filename, Texture& out_texture);

		const int LoadModels(std::string directory);
		bool LoadScenes(std::string directory);

	};
}