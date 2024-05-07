#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "APIs/OpenGL/OpenGL4Api.h"

#define USE_OPENGL(V) V = new OpenGL::OpenGL4Api();
//#define USE_DIRECT3D(V) V = new Direct3DApi();
//#define USE_DIRECTXII(V) V = new DirectX12Api();
//#define USE_VULKAN(V) V = new VulkanApi();


int main()
{
	Engine::IGPUApi* gpuapi;

	USE_OPENGL(gpuapi)

	gpuapi->Initialize();
	gpuapi->LoadFiles();
	gpuapi->Start();

	while (gpuapi->IsWindowOpen())
	{
		gpuapi->DequeueEvents();
		gpuapi->Update();

		gpuapi->Clear();
		gpuapi->Draw();
		gpuapi->Present();
	}

	gpuapi->Exit();

	delete gpuapi;

	return 0;
}