#pragma once
#include "../GreenCowEngine.h"
#include "Pipeline.h"
#include "GameObject.h"

namespace OpenGL
{
	class Camera;
	class Mesh;
	class Scene : public Engine::IScene
	{
		public:

		Scene(Pipeline* pipeline) : refPipeline(pipeline)
		{
			ActiveCamera = new Camera();
		}

		void Load(const char* scene_filename);
		void Unload();
		void Init();
		void Update(const float deltaTime);
		void Draw();

		Camera* ActiveCamera;
		Pipeline* refPipeline;
		std::vector<GameObject*> GameObjects{};
	};
}