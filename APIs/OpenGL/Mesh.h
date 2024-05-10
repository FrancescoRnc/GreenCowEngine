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

		GLuint VAO = 0; 
		GLuint VBO = 0;
		GLuint EBO = 0;
		GLuint Texture = 0;
		GLuint Override_Program = 0;
		glm::mat4 ModelMatrix{ glm::mat4(1.0f) };

		Camera* refCamera;
		float angle = 0.f;

		//friend class Transform;
		Engine::Transform transform = {};


		private:


	};
}