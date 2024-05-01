#include "OpenGL4Time.h"

const float GreenCow::OpenGL4Time::GetDelta()
{
	now = glfwGetTime();
	float delta = now - last;
	last = now;
	return delta;
}