#pragma once
#include "../GreenCowEngine.h"
#include "OpenGL4Camera.h"

namespace GreenCow
{
	class OpenGL4Mesh : public GPUMesh
	{
		public:
		OpenGL4Mesh(OpenGL4Camera* _refCamera) : refCamera(_refCamera) {}

		// Inherited via GPUMesh
		void Setup(std::vector<Vertex> vertices, std::vector<GLint> indices) override;
		void Draw(GLuint program) override;
		// - - - -

		//void RegisterVertices(OpenGL4Pipeline* pipeline);

		std::vector<Vertex> Vertices;
		std::vector<GLint> Indices;

		GLuint VAO, VBO, EBO, Texture, Override_Program;
		glm::mat4 ModelMatrix;

		OpenGL4Camera* refCamera;
		float angle = 0.f;

		//friend class Transform;
		Transform transform = {};


		private:


	};
}