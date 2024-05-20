#include "Time.h"

const double OpenGL::Time::GetDelta()
{
	now = glfwGetTime();
	double delta = now - last;
	last = now;
	return delta;
}