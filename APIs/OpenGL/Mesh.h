#pragma once
#include "../Engine/GreenCowEngine.h"
#include "Camera.h"
#include "Material.h"

namespace OpenGL
{
	struct MeshData
	{
		std::string Name{""};
		std::vector<Vertex> Vertices{};
		std::vector<GLint> Indices{};
		GLuint VAO = 0;
		GLuint VBO = 0;
		GLuint EBO = 0;

		MeshData() {}

		MeshData(
			const std::string name, 
			const std::vector<Vertex> vertices, 
			const std::vector<GLint> indices, 
			const GLuint vao, 
			const GLuint vbo, 
			const GLuint ebo) 
			: Name(name), Vertices(vertices), Indices(indices), VAO(vao), VBO(vbo), EBO(ebo)
		{ }

	private:
		//static unsigned int meshCount;
	};

	class Mesh : public Engine::GPUMesh
	{
	public:
		Mesh(MeshData* data, Material* mat) : Data(data), CurrentMaterial(mat) {}

		// Inherited via GPUMesh
		void Setup(std::vector<Engine::Vertex> vertices, std::vector<GLint> indices) override;
		// - - - -
				
		void Draw();

		MeshData* Data;
		Material* CurrentMaterial;

		glm::mat4 ModelMatrix{ glm::mat4(1.0f) };
	};


	struct MeshInstanceProfile
	{
		GLuint Program{ 0 };
		std::string MeshName{ "" };
		std::string MaterialName{ "" };
		std::vector<glm::mat4> Models{};

		inline size_t Count() { return Models.size(); }
	};
}