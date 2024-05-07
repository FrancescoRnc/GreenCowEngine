#pragma once
#include "../GreenCowEngine.h";
#include "Texture.h"

namespace OpenGL
{
	class Material
	{
		GLuint Program;

		public:
		Material(GLuint defaulProgram) : Program(defaulProgram)
		{}

		std::vector<Texture*> Textures;

		inline GLuint GetProgram() const
		{
			return Program;
		}
	};
}
