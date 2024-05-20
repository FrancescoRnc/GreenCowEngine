#pragma once
#include "../Engine/GreenCowEngine.h"
#include "Pipeline.h"
#include "GameObject.h"

namespace OpenGL
{
	class Camera;
	class Mesh;
	class Scene : public Engine::IScene
	{
		public:

		Scene()
		{
			ActiveCamera = new Camera();
		}

		void Load(const char* scene_filename) override;
		void Unload() override;
		void Init() override;
		void Update(const float deltaTime) override;

		Camera* ActiveCamera;
		std::vector<GameObject*> GameObjects{};
	};
}