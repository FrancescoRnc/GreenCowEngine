#pragma once
#include "../GreenCowEngine.h" 

namespace OpenGL
{
	class Texture : public ITexture
	{
		GLuint TextureID;

		void Setup();
	};
}