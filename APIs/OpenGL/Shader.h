#pragma once
#include "../Engine/GreenCowEngine.h"

namespace OpenGL
{
	struct Shader
	{
		GLuint Program;
		std::vector<const char*> Uniforms;

		Shader(GLuint program) : Program(program), Uniforms({}) { }
	};
}
