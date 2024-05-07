#pragma once
#include "../GreenCowEngine.h"
#include "Camera.h"

namespace OpenGL
{
	class Mesh : public Engine::GPUMesh
	{
		public:
		Mesh(Camera* _refCamera) : refCamera(_refCamera) {}

		// Inherited via GPUMesh
		void Setup(std::vector<Engine::Vertex> vertices, std::vector<GLint> indices) override;
		void Draw(uint32_t program) override;
		// - - - -

		//void RegisterVertices(Pipeline* pipeline);

		std::vector<Engine::Vertex> Vertices;
		std::vector<GLint> Indices;

		GLuint VAO, VBO, EBO, Texture, Override_Program;
		glm::mat4 ModelMatrix;

		Camera* refCamera;
		float angle = 0.f;

		//friend class Transform;
		Engine::Transform transform = {};


		private:


	};
}