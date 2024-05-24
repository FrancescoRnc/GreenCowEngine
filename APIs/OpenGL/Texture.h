#pragma once
#include "../Engine/GreenCowEngine.h" 

namespace OpenGL
{
	class Texture : public ITexture
	{
	public:
		Texture() {}
		Texture(GLuint texId) : TextureID(texId) {}
		//Texture(GLuint texId, std::vector<unsigned char> source) 
		//	: TextureID(texId), Source(source)
		//{}

		GLuint TextureID{ 0 };
		//std::vector<unsigned char> Source{};

		void Setup();
		void Bind();
	};
}