#pragma once
#include "GreenCowEngine.h"
#include "IGPUApi.h"

namespace Engine
{
	class GameApplication
	{
		IGPUApi* gpuapi{ nullptr };


	public:
		GameApplication(IGPUApi* api) : gpuapi(api)
		{

		}

		void Initialize();

		void Run();

		void Exit();
	};
}

