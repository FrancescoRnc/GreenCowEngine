#include "Time.h"

const float OpenGL::Time::GetDelta()
{
	now = glfwGetTime();
	float delta = now - last;
	last = now;
	return delta;
}