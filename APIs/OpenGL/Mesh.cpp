#include "Mesh.h"

void OpenGL::Mesh::Setup(std::vector<Vertex> vertices, std::vector<int> indices)
{
	/*Data.Vertices = vertices;
	Data.Indices = indices;

	glGenVertexArrays(1, &Data.VAO);
	glBindVertexArray(Data.VAO);

	glGenBuffers(1, &Data.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, Data.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(),
		&Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &Data.EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Data.EBO);
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
	glBindVertexArray(0);*/
}

/*void OpenGL::Mesh::Draw(uint32_t program)
{
	glUseProgram(program);

	const glm::mat4 camMatrix = refCamera->GetProjection() * refCamera->GetView();
	GLint camLoc = glGetUniformLocation(program, "camMatrix");
	glUniformMatrix4fv(camLoc, 1, GL_FALSE, glm::value_ptr(camMatrix));
	GLint modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(ModelMatrix));

	glBindTexture(GL_TEXTURE_2D, Texture);

	glBindVertexArray(VAO);
	//glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(Vertices.size()));
	glBindVertexArray(0);

}*/


void OpenGL::Mesh::Draw()
{
	//glUseProgram(DefaultProgram);

	//const glm::mat4 camMatrix = refCamera->GetProjection() * refCamera->GetView();
	//GLint camLoc = glGetUniformLocation(program, "camMatrix");
	//glUniformMatrix4fv(camLoc, 1, GL_FALSE, glm::value_ptr(camMatrix));
	//GLint modelLoc = glGetUniformLocation(program, "model");
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(ModelMatrix));

	//glBindTexture(GL_TEXTURE_2D, Texture);

	//glBindVertexArray(VAO);
	//glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(Vertices.size()));
	//glBindVertexArray(0);

}