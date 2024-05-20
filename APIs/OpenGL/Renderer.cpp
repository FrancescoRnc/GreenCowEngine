#include "Renderer.h"


void OpenGL::Renderer::InjectMeshes(std::vector<Mesh*> inMeshes)
{
	meshes = inMeshes;
}

void OpenGL::Renderer::Draw()
{
	const GLuint defaultProgram = pipeline->DefaultProgram();
	glUseProgram(defaultProgram);

	for (auto mesh : meshes)
	{
		glUseProgram(mesh->CurrentMaterial->GetProgram());
		
		mesh->CurrentMaterial->ApplyUniformMat4To("camMatrix", refCamera->GetView() * refCamera->GetProjection());
		mesh->CurrentMaterial->ApplyMat4Uniforms(
			{
				{"camMatrix", refCamera->GetView() * refCamera->GetProjection()},
				{"model", mesh->ModelMatrix}
			});

		glBindVertexArray(mesh->Data->VAO);
		//glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(mesh->Data->Vertices.size()));
		glBindVertexArray(0);
	}
}

