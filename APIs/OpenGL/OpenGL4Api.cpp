#include "OpenGL4Api.h"
#include <stb/stb_image.h>

#include "Window.h"
#include "Camera.h"
#include "Mesh.h"
#include "Pipeline.h"
#include "Renderer.h"
#include "FileLoader.h"
#include "Scene.h"
#include "../Helpers/FileReader.h"



// API
OpenGL::OpenGL4Api::OpenGL4Api()
{
	window = new Window();
	pipeline = new Pipeline();
	//renderer = new Renderer(pipeline);
	InputPressMatcher = new Engine::FunctionMatcher<int>(0, []() 
		{ /*std::cout << "Press nothing." << std::endl;*/ });
	InputReleaseMatcher = new Engine::FunctionMatcher<int>(0, []() 
		{ /*std::cout << "Release nothing." << std::endl;*/ });

	activeScene = new Scene();


	time = {};
}

void OpenGL::OpenGL4Api::CallKeyFunc(int action, int key)
{
	if (action == GLFW_PRESS) InputPressMatcher->Call(key);
	else if (action == GLFW_RELEASE) InputReleaseMatcher->Call(key);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//std::cout << action << " " << key << std::endl;
	auto self = reinterpret_cast<OpenGL::OpenGL4Api*>(glfwGetWindowUserPointer(window));
	self->CallKeyFunc(action, key);
}
void window_close_callback(GLFWwindow* window)
{
	auto self = reinterpret_cast<OpenGL::OpenGL4Api*>(glfwGetWindowUserPointer(window));
	self->window->Close();
}

void OpenGL::OpenGL4Api::Initialize()
{
	std::cout << "OpenGL: ";
	std::cout << "Initialization" << std::endl;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window->Create("GreenCow Engine", 800, 600);
	glfwSetWindowUserPointer(window->GetWindowData(), this);

	glEnable(GL_DEPTH_TEST);

	SetupInputBinding();
}

void OpenGL::OpenGL4Api::LoadFiles()
{
	std::cout << "OpenGL: ";
	std::cout << "Loading Files..." << std::endl;

	try
	{
		pipeline->CreateProgram("default", {
			"Assets/Shaders/Mesh.vert",
			"Assets/Shaders/Mesh.frag"
		});
		pipeline->CreateProgram("textured", {
			"Assets/Shaders/Mesh.vert",
			"Assets/Shaders/Textured.frag"
		}, true);
	}
	catch (const std::exception& ex) 
	{
		std::cout << "Error during files loading!" << ex.what() << std::endl;
	}
}

void OpenGL::OpenGL4Api::Start() 
{
	activeScene->Init();
	// TODO: Butta le mesh dentro Pipeline
	window->Show();
}

bool OpenGL::OpenGL4Api::IsWindowOpen()
{
	return window->IsOpen;
}

void OpenGL::OpenGL4Api::DequeueEvents()
{
	glfwPollEvents();
}

void OpenGL::OpenGL4Api::Update()
{
	const double deltatime = time.GetDelta();
	std::cout << "\rFPS: " << 1 / deltatime;

	activeScene->Update((float)deltatime);
}

void OpenGL::OpenGL4Api::Clear()
{
	window->Clear();
}

void OpenGL::OpenGL4Api::Draw()
{
	pipeline->Draw();
}

void OpenGL::OpenGL4Api::Present()
{
	window->Present();
}

void OpenGL::OpenGL4Api::Exit()
{
	std::cout << std::endl;
	std::cout << "OpenGL: ";
	std::cout << "Exiting Program..." << std::endl;

	window->Destroy();
	glfwTerminate();

}

void OpenGL::OpenGL4Api::SetupInputBinding()
{
	glfwSetKeyCallback(window->GetWindowData(), (GLFWkeyfun)key_callback);
	glfwSetWindowCloseCallback(window->GetWindowData(),
		(GLFWwindowclosefun)window_close_callback);

	InputPressMatcher->Add(GLFW_KEY_ESCAPE, [this]() { window->Close(); });
	InputPressMatcher->Add(GLFW_KEY_W, [this]() { movespd = 10.f;  });
	InputPressMatcher->Add(GLFW_KEY_S, [this]() { movespd = -10.f; });
	InputPressMatcher->Add(GLFW_KEY_D, [this]() { angspd = 5.f; });
	InputPressMatcher->Add(GLFW_KEY_A, [this]() { angspd = -5.f; });

	InputReleaseMatcher->Add(GLFW_KEY_W, [this]() { movespd = 0.0; });
	InputReleaseMatcher->Add(GLFW_KEY_S, [this]() { movespd = 0.0; });
	InputReleaseMatcher->Add(GLFW_KEY_D, [this]() { angspd = 0.0; });
	InputReleaseMatcher->Add(GLFW_KEY_A, [this]() { angspd = 0.0; });
	InputReleaseMatcher->Add(GLFW_KEY_ESCAPE, [this]() { window->Close(); });
}
