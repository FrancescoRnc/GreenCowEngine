#include "Mesh.h"

void OpenGL::Mesh::Setup(std::vector<Vertex> vertices, std::vector<int> indices)
{
	Vertices = vertices;
	Indices = indices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(),
		&Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * Indices.size(),
		&Indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Vertex::normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Vertex::texCoords));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void OpenGL::Mesh::Draw(uint32_t program)
{
	//ModelMatrix = glm::mat4(1.0f);
	//glm::mat4 TranslationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	//glm::mat4 RotationMatrix = glm::rotate(glm::mat4(1.0f), 3.14f / 4, glm::vec3(0.0f, 1.0f, 0.0f));
	//glm::mat4 ScaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 1.0f));	
	//ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;

	//transform.Translate(glm::vec3(0.0f, 0.0f, -1.0f));
	//transform.Rotate(glm::vec3(0.0f, 1.0f, 0.0f), 3.14f / 4);
	//transform.ReScale(glm::vec3(1.0f));
	transform.modelMatrix = transform.translationMatrix 
							* transform.rotationMatrix 
							* transform.scaleMatrix;

	glUseProgram(program);

	//GLint viewLoc = glGetUniformLocation(program, "view");
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(refCamera->GetView()));
	//GLint projLoc = glGetUniformLocation(program, "projection");
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(refCamera->GetProjection()));
	const glm::mat4 camMatrix = refCamera->GetProjection() * refCamera->GetView();
	GLint camLoc = glGetUniformLocation(program, "camMatrix");
	glUniformMatrix4fv(camLoc, 1, GL_FALSE, glm::value_ptr(camMatrix));
	GLint modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform.modelMatrix));

	//if (Texture)
		glBindTexture(GL_TEXTURE_2D, Texture);

	glBindVertexArray(VAO);
	//glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(Vertices.size()));
	glBindVertexArray(0);

}

//void OpenGL::Mesh::RegisterVertices(Pipeline* pipeline)
//{
//	pipeline->TotalVertices.insert(pipeline->TotalVertices.begin(), 
//								   Vertices.begin(), Vertices.end());
//	pipeline->TotalIndices.insert(pipeline->TotalIndices.begin(),
//								  Indices.begin(), Indices.end());
//}