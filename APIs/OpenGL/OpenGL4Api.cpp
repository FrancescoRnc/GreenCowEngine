#include "OpenGL4Api.h"
#include <stb/stb_image.h>

#include "OpenGL4Window.h"
#include "OpenGL4Camera.h"
#include "OpenGL4Mesh.h"
#include "OpenGL4Pipeline.h"
#include "OpenGL4FileLoader.h"
#include "OpenGL4Scene.h"
#include "../Helpers/FileReader.h"


// API
GreenCow::OpenGL4Api::OpenGL4Api()
{
	window = new OpenGL4Window();
	pipeline = new OpenGL4Pipeline();
	InputPressMatcher =
		new FunctionMatcher<int>(0, []() { /*std::cout << "Press nothing." << std::endl;*/ });
	InputReleaseMatcher =
		new FunctionMatcher<int>(0, []() { /*std::cout << "Release nothing." << std::endl;*/ });

	camera = new OpenGL4Camera();
	//mesh = new OpenGL4Mesh(camera);
	scene = new OpenGL4Scene();
}

void GreenCow::OpenGL4Api::CallKeyFunc(int action, int key)
{
	if (action == GLFW_PRESS) InputPressMatcher->Call(key);
	else if (action == GLFW_RELEASE) InputReleaseMatcher->Call(key);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//std::cout << action << " " << key << std::endl;
	auto self = reinterpret_cast<GreenCow::OpenGL4Api*>(glfwGetWindowUserPointer(window));
	self->CallKeyFunc(action, key);
}
void window_close_callback(GLFWwindow* window)
{
	auto self = reinterpret_cast<GreenCow::OpenGL4Api*>(glfwGetWindowUserPointer(window));
	self->window->Close();
}

void GreenCow::OpenGL4Api::Initialize()
{
	std::cout << "OpenGL: ";
	std::cout << "Initialization" << std::endl;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	const int windowWidth = 800;
	const int windowHeight = 600;
	window->Create("GreenCow Engine", windowWidth, windowHeight);
	camera->Setup(60, windowWidth, windowHeight, 0.01f, 1000.f);
	camera->Target = { 0.0f, 0.0f, 1.0f };
	scene->Load("");

	glEnable(GL_DEPTH_TEST);
	glfwSetWindowUserPointer(window->GetWindowData(), this);

	SetupInputBinding();
}

void GreenCow::OpenGL4Api::LoadFiles()
{
	std::cout << "OpenGL: ";
	std::cout << "Loading Files..." << std::endl;


	try
	{
		pipeline->CreateProgram("Mesh");
		//std::cout << content.source << std::endl;

		OpenGL4FileLoader loader;
		std::vector<Vertex> vertices;
		std::vector<GLint> indices;

		if (!loader.LoadModel("Assets/Models/model_cow.obj", vertices, indices)) {
			return;
		}

		//mesh->Setup(vertices, indices);
		//mesh->transform.Translate({ 0.0f, 0.0f, -4.0f });
		////mesh->transform.Rotate({0.0f, 1.0f, 0.0f}, 3.14f / 4);
		//mesh->transform.ReScale(glm::vec3(1.0f));
		//mesh->Texture = loader.LoadTexture("Assets/Textures/ground.jpg");
	}
	catch (const std::exception& ex) {
		std::cout << "Error during files loading!!!" << std::endl;
		return;
	}
}

bool GreenCow::OpenGL4Api::IsWindowOpen()
{
	return window->IsOpen;
}

void GreenCow::OpenGL4Api::DequeueEvents()
{
	glfwPollEvents();
}

void GreenCow::OpenGL4Api::Update()
{
	//std::cout << "FPS: " << 1 / deltatime << std::endl;
	const float deltatime = time.GetDelta();

	scene->Update(deltatime);

	camera->Update();

	//if (!mesh) return;
	//mesh->transform.AddRotation({ 0.0f, 1.0f, 0.0f }, angspd * deltatime);
	//mesh->transform.AddTranslation(glm::vec3(0.0f, 0.0f, 1.0f) * movespd * deltatime);
}

void GreenCow::OpenGL4Api::Clear()
{
	window->Clear();
}

void GreenCow::OpenGL4Api::Draw()
{
	//mesh->Draw(pipeline->Program);
	scene->Draw();
}

void GreenCow::OpenGL4Api::Present()
{
	window->Present();
}

void GreenCow::OpenGL4Api::Exit()
{
	std::cout << "OpenGL: ";
	std::cout << "Exiting Program..." << std::endl;

	window->Destroy();
	glfwTerminate();

}

void GreenCow::OpenGL4Api::SetupInputBinding()
{
	glfwSetKeyCallback(window->GetWindowData(), (GLFWkeyfun)key_callback);
	glfwSetWindowCloseCallback(window->GetWindowData(),
		(GLFWwindowclosefun)window_close_callback);
	//InputPressMatcher->Add(GLFW_KEY_ESCAPE, [this]() { window->Close(); });
	InputPressMatcher->Add(GLFW_KEY_W, [this]() { movespd = 10.f; });
	InputPressMatcher->Add(GLFW_KEY_S, [this]() { movespd = -10.f; });
	InputPressMatcher->Add(GLFW_KEY_D, [this]() { angspd = 5.f; });
	InputPressMatcher->Add(GLFW_KEY_A, [this]() { angspd = -5.f; });

	InputReleaseMatcher->Add(GLFW_KEY_W, [this]() { movespd = 0.0; });
	InputReleaseMatcher->Add(GLFW_KEY_S, [this]() { movespd = 0.0; });
	InputReleaseMatcher->Add(GLFW_KEY_D, [this]() { angspd = 0.0; });
	InputReleaseMatcher->Add(GLFW_KEY_A, [this]() { angspd = 0.0; });
	InputReleaseMatcher->Add(GLFW_KEY_ESCAPE, [this]() { window->Close(); });
}
