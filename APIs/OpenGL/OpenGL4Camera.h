#pragma once
#include "../GreenCowEngine.h"

namespace GreenCow
{
	class OpenGL4Camera : public ICamera
	{
		public:

		void Setup(const GLfloat FOV, const GLfloat width, const GLfloat height,
				   const GLfloat znear, const GLfloat zfar) override;

		// Inherited via ICamera
		void LookAt(const glm::vec3 target) override;
		void Orbit(const glm::vec3 target, const float distance,
				   const float deltaRad) override;
		virtual void Update() override;
		// - - - -

		const glm::mat4 GetView() const { return viewMatrix; }
		const glm::mat4 GetProjection() const { return projectionMatrix; }
		const glm::vec3 GetPosition() const { return glm::vec3(0.f); }
		const glm::vec3 GetDirection() const { return glm::vec3(0.f); }
		const glm::quat GetRotation() const { return glm::quat(1.f, 0.f, 0.f, 0.f); }

		Transform transform;
		glm::vec3 Target = { 0.0f, 0.0f, 1.0f };

		private:

		glm::mat4 viewMatrix, projectionMatrix, orthoMatrix;
		
		GLfloat FOV = 0.0f; 
		GLfloat viewWidth = 0.0f;
		GLfloat viewHeight = 0.0f;
		GLfloat znear = 0.0f;
		GLfloat zfar = 0.0f;
	};
}