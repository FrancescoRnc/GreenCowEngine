#include "OpenGL4Api.h"
#include <stb/stb_image.h>

#include "Window.h"
#include "Camera.h"
#include "Mesh.h"
#include "Pipeline.h"
#include "FileLoader.h"
#include "Scene.h"
#include "../Helpers/FileReader.h"



// API
OpenGL::OpenGL4Api::OpenGL4Api()
{
	window = new Window();
	pipeline = new Pipeline();
	InputPressMatcher =
		new Engine::FunctionMatcher<int>(0, []() { /*std::cout << "Press nothing." << std::endl;*/ });
	InputReleaseMatcher =
		new Engine::FunctionMatcher<int>(0, []() { /*std::cout << "Release nothing." << std::endl;*/ });

	//camera = new Camera();
	//mesh = new Mesh(camera);
	activeScene = new Scene(pipeline);
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

	//const int windowWidth = 800;
	//const int windowHeight = 600;
	
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

		pipeline->SerializePrograms();

		/*std::cout << content.source << std::endl;
		FileLoader loader;
		std::vector<Vertex> vertices;
		std::vector<GLint> indices;

		if (!loader.LoadModel(relativeAssetDirectory + "Models/model_cow.obj", vertices, indices)) {
			return;
		}
		mesh->Setup(vertices, indices);
		mesh->transform.Translate({ 0.0f, 0.0f, -4.0f });
		//mesh->transform.Rotate({0.0f, 1.0f, 0.0f}, 3.14f / 4);
		mesh->transform.ReScale(glm::vec3(1.0f));
		mesh->Texture = loader.LoadTexture("Assets/Textures/ground.jpg");*/
	}
	catch (const std::exception& ex) {
		std::cout << "Error during files loading!!!" << std::endl;
		return;
	}
}

void OpenGL::OpenGL4Api::Start() 
{
	activeScene->Init();

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
	//std::cout << "FPS: " << 1 / deltatime << std::endl;
	const float deltatime = time.GetDelta();

	activeScene->Update(deltatime);

	//camera->Update();

	//if (!mesh) return;
	//mesh->transform.AddRotation({ 0.0f, 1.0f, 0.0f }, angspd * deltatime);
	//mesh->transform.AddTranslation(glm::vec3(0.0f, 0.0f, 1.0f) * movespd * deltatime);
}

void OpenGL::OpenGL4Api::Clear()
{
	window->Clear();
}

void OpenGL::OpenGL4Api::Draw()
{
	//mesh->Draw(pipeline->Program);
	activeScene->Draw();
}

void OpenGL::OpenGL4Api::Present()
{
	window->Present();
}

void OpenGL::OpenGL4Api::Exit()
{
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
