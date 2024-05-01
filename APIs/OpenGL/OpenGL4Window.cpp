#include "OpenGL4Window.h"

void GreenCow::OpenGL4Window::Create(const char* title, const int width, const int height)
{
	std::cout << "OpenGL: Creating Window..." << std::endl;
	internal_window = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(internal_window);
	gladLoadGL();
	glViewport(0, 0, width, height);
	clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
}

void GreenCow::OpenGL4Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
}

void GreenCow::OpenGL4Window::Present()
{
	glfwSwapBuffers(internal_window);
}

bool GreenCow::OpenGL4Window::Close()
{
	IsOpen = false;
	return false;
}

void GreenCow::OpenGL4Window::Destroy()
{
	glfwDestroyWindow(internal_window);
}

GreenCow::OpenGL4Window::~OpenGL4Window()
{

}