#pragma once
#include "../Engine/GreenCowEngine.h"

namespace OpenGL
{
	struct CameraPerspectiveInfo
	{
		float FOV = 0.0f;
		float Aspect = 0.0f;
		float zNear = 0.0f;
		float zFar = 0.0f;

		CameraPerspectiveInfo(
			const float _fov = 0.0f,
			const float _aspect = 0.0f,
			const float _zNear = 0.0f, 
			const float _zFar = 0.0f)
			: FOV(_fov), Aspect(_aspect), zNear(_zNear), zFar(_zFar)
		{}

		inline glm::mat4 GetPerspective() const
		{
			return glm::perspective(FOV, Aspect, zNear, zFar);
		}
	};

	class Camera : public Engine::ICamera
	{
		public:

		void Setup(const float FOV, const float width, const float height,
				   const float znear, const float zfar) override;

		// Inherited via ICamera
		void LookAt(const glm::vec3 target) override;
		void SetPerspective(const float fov, const float aspect, const float znear, const float zfar) override;
		void SetFOV(const float fov);
		void Orbit(const glm::vec3 target, const float distance,
				   const float deltaRad) override;
		virtual void Update() override;
		// - - - -

		const glm::mat4 GetView() override { return viewMatrix; }
		const glm::mat4 GetProjection() override { return projectionMatrix; }
		const glm::vec3 GetPosition() const { return glm::vec3(0.f); }
		const glm::vec3 GetDirection() const { return glm::vec3(0.f); }
		const glm::quat GetRotation() const { return glm::quat(1.f, 0.f, 0.f, 0.f); }

		Engine::Transform transform;
		glm::vec3 Target = { 0.0f, 0.0f, 1.0f };

		private:

		glm::mat4 viewMatrix{glm::mat4(1.0f)}, projectionMatrix{ glm::mat4(1.0f) }, orthoMatrix{ glm::mat4(1.0f) };
		
		CameraPerspectiveInfo info{};
	};
}