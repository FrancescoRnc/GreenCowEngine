#pragma once
#include "../GreenCowEngine.h"

namespace GreenCow
{
	class OpenGL4Camera;
	class OpenGL4Mesh;
	class OpenGL4Scene : public IScene
	{
		public:

		void Load(const char* scene_filename);
		void Unload();
		void Update(const float deltaTime);
		void Draw();

		OpenGL4Camera* refCamera;
		std::vector<OpenGL4Mesh*> Meshes;
	};
}