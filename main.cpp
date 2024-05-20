#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "APIs/OpenGL/OpenGL4Api.h"
#include "APIs/Engine/GameApplication.h"

#define USE_OPENGL(V) V = new OpenGL::OpenGL4Api();
//#define USE_DIRECT3D(V) V = new Direct3DApi();
//#define USE_DIRECTXII(V) V = new DirectX12Api();
//#define USE_VULKAN(V) V = new VulkanApi();


int main()
{
	Engine::IGPUApi* gpuapi;

	USE_OPENGL(gpuapi)

	GameApplication* app = new GameApplication(gpuapi);

	app->Initialize();

	app->Run();	

	app->Exit();

	delete app;
	delete gpuapi;

	return 0;
}