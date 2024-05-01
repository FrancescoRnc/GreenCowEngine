#pragma once
#include "../GreenCowEngine.h" 

namespace GreenCow
{
	class OpenGL4Texture : public ITexture
	{
		GLuint TextureID;

		void Setup();
	};
}