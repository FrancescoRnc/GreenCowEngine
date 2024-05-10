#pragma once
#include "GreenCowEngine.h"

namespace Engine
{
	class Transform
	{
	public:

		static glm::vec3 UP;
		static glm::vec3 RIGHT;
		static glm::vec3 FRONT;

		glm::vec3 Position, Rotation, Scale;
		glm::vec3 Right;
		glm::vec3 Up;
		glm::vec3 Front;
		float Angle;

		inline glm::mat4 GetModel() const
		{
			return translationMatrix * rotationMatrix * scaleMatrix;
		}

		void Translate(const glm::vec3 newPos);
		void AddTranslation(const glm::vec3 delta);

		void Rotate(const glm::vec3 axis, const float angleRad);
		void AddRotation(const glm::vec3 axis, const float deltaAngleRad);

		void ReScale(const glm::vec3 newSc);
		void AddScale(const glm::vec3 delta);

		//glm::vec3 Forward()
		//{
		//	return glm::cross()
		//}

		//private:
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		glm::mat4 translationMatrix = glm::mat4(1.0f);
		glm::mat4 rotationMatrix = glm::mat4(1.0f);
		glm::mat4 scaleMatrix = glm::mat4(1.0f);

		glm::mat4 forward = glm::mat4(1.0f);
		glm::mat4 right = glm::mat4(1.0f);
		glm::mat4 up = glm::mat4(1.0f);
	};
}
