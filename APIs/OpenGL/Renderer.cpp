#include "Renderer.h"


void OpenGL::Renderer::Draw()
{
	const GLuint program = pipeline->DefaultProgram();
	glUseProgram(program);

	for (auto drawable : drawables)
	{
		drawable->Draw();
	}
}