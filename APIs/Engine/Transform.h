#pragma once
#include "GreenCowEngine.h"

namespace Engine
{
	class Transform
	{
	public:

		static glm::vec3 UP;
		static glm::vec3 RIGHT;
		static glm::vec3 FORWARD;

		glm::vec3 up{};
		glm::vec3 right{};
		glm::vec3 forward{};

		glm::vec3 Position{}, Rotation{}, Scale{};
		float Angle{ 0 };

		//glm::vec3 Right() 
		//{
		//	return glm::normalize(glm::vec3(modelMatrix[0]));
		//}
		//glm::vec3 Up()
		//{
		//	return glm::normalize(glm::vec3(modelMatrix[1]));
		//}
		//glm::vec3 Forward()
		//{
		//	return glm::normalize(glm::vec3(modelMatrix[2]));
		//}

		glm::mat4 GetModel();

		void Translate(const glm::vec3 newPos);
		void AddTranslation(const glm::vec3 delta);

		void Rotate(const glm::vec3 axis, const float angleRad);
		void AddRotation(const glm::vec3 axis, const float deltaAngleRad);

		void ReScale(const glm::vec3 newSc);
		void AddScale(const glm::vec3 delta);


		//private:
		glm::mat4 ModelMatrix = glm::mat4(1.0f);
		glm::mat4 translationMatrix = glm::mat4(1.0f);
		glm::mat4 rotationMatrix = glm::mat4(1.0f);
		glm::mat4 scaleMatrix = glm::mat4(1.0f);

		//glm::mat4 pitch = glm::mat4(1.0f); // right
		//glm::mat4 yaw = glm::mat4(1.0f); // up
		//glm::mat4 roll = glm::mat4(1.0f); // forward
	};
}
