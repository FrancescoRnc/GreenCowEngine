#pragma once
#include "../GreenCowEngine.h" 

namespace OpenGL
{
	class Texture : public Engine::ITexture
	{
		GLuint TextureID;

		void Setup();
	};
}