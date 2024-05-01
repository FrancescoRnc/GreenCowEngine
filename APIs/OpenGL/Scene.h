#pragma once
#include "../GreenCowEngine.h"

namespace OpenGL
{
	class Camera;
	class Mesh;
	class Scene : public Engine::IScene
	{
		public:

		void Load(const char* scene_filename);
		void Unload();
		void Update(const float deltaTime);
		void Draw();

		Camera* refCamera;
		std::vector<Mesh*> Meshes;
	};
}