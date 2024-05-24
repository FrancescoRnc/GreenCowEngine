#include "GameApplication.h"

void Engine::GameApplication::Initialize()
{
	loader->LoadFrom("Assets");

	gpuapi->Initialize();
	gpuapi->LoadFiles();
	gpuapi->Start();
}

void Engine::GameApplication::Run()
{
	while (gpuapi->IsWindowOpen())
	{
		//gpuapi->DequeueEvents();
		glfwPollEvents();
		gpuapi->Update();

		gpuapi->Clear();
		gpuapi->Draw();
		gpuapi->Present();
	}
}

void Engine::GameApplication::Exit()
{
	gpuapi->Exit();
}
