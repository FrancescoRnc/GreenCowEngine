#pragma once
#include "../GreenCowEngine.h"

namespace OpenGL
{
	class Camera : public Engine::ICamera
	{
		public:

		void Setup(const float FOV, const float width, const float height,
				   const float znear, const float zfar) override;

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

		Engine::Transform transform;
		glm::vec3 Target = { 0.0f, 0.0f, 1.0f };

		private:

		glm::mat4 viewMatrix{glm::mat4(1.0f)}, projectionMatrix{ glm::mat4(1.0f) }, orthoMatrix{ glm::mat4(1.0f) };
		
		GLfloat FOV = 0.0f; 
		GLfloat viewWidth = 0.0f;
		GLfloat viewHeight = 0.0f;
		GLfloat znear = 0.0f;
		GLfloat zfar = 0.0f;
	};
}