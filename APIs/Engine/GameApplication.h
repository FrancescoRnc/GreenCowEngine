#pragma once
#include "GreenCowEngine.h"
#include "IGPUApi.h"

namespace Engine
{
	class GameApplication
	{
		IGPUApi* gpuapi{ nullptr };
		Helpers::AssetManager* loader{ nullptr };

	public:
		GameApplication(IGPUApi* api) : gpuapi(api)
		{
			loader = new Helpers::AssetManager();
		}

		void Initialize();

		void Run();

		void Exit();
	};
}

