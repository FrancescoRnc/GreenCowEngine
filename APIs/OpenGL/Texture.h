#pragma once
#include "../Engine/GreenCowEngine.h" 

namespace OpenGL
{
	class Texture : public ITexture
	{
	public:
		Texture() {}
		Texture(GLuint texId, unsigned char* source) 
			: TextureID(texId), Source(source)
		{}

		GLuint TextureID{ 0 };
		unsigned char* Source{ nullptr };

		void Setup();
		void Bind();
	};
}