#include "Window.h"

void OpenGL::Window::Create(const char* title, const int width, const int height)
{
	std::cout << "OpenGL: Creating Window..." << std::endl;
	internal_window = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(internal_window);
	gladLoadGL();
	glViewport(0, 0, width, height);
	clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
}

void OpenGL::Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
}

void OpenGL::Window::Present()
{
	glfwSwapBuffers(internal_window);
}

bool OpenGL::Window::Close()
{
	IsOpen = false;
	return false;
}

void OpenGL::Window::Destroy()
{
	glfwDestroyWindow(internal_window);
}

OpenGL::Window::~Window()
{

}