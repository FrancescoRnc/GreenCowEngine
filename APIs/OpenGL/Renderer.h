#pragma once
#include "../GreenCowEngine.h"
#include "Pipeline.h"
#include "Shader.h"

namespace OpenGL
{
	class Renderer
	{
		Pipeline* pipeline;
		Shader* defaultShader;
		std::vector<IDrawable*> drawables;


		void Draw();
	};
}

