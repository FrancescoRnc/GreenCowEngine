#include "Transform.h"

glm::vec3 Engine::Transform::UP = { 0.0f, 1.0f, 0.0f };
glm::vec3 Engine::Transform::RIGHT = { 1.0f, 0.0f, 0.0f };
glm::vec3 Engine::Transform::FRONT = { 0.0f, 0.0f, 1.0f };

void Engine::Transform::Translate(const glm::vec3 newPos)
{
	Position = newPos;
	translationMatrix = glm::translate(glm::mat4(1.0f), newPos);
}
void Engine::Transform::AddTranslation(const glm::vec3 delta)
{
	Position += delta;
	translationMatrix = glm::translate(glm::mat4(1.0f), Position);
}

void Engine::Transform::Rotate(const glm::vec3 axis, const float angleRad)
{
	Angle = angleRad;
	rotationMatrix = glm::rotate(glm::mat4(1.0f), angleRad, axis);
}
void Engine::Transform::AddRotation(const glm::vec3 axis, const float deltaAngleRad)
{
	Angle += deltaAngleRad;
	rotationMatrix = glm::rotate(glm::mat4(1.0f), Angle, axis);
}

void Engine::Transform::ReScale(const glm::vec3 newSc)
{
	Scale = newSc;
	scaleMatrix = glm::scale(glm::mat4(1.0f), Scale);
}
void Engine::Transform::AddScale(const glm::vec3 delta)
{
	Scale += delta;
	scaleMatrix = glm::scale(glm::mat4(1.0f), Scale);
}