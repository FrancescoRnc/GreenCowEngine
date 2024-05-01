#include "OpenGL4Camera.h"

void GreenCow::OpenGL4Camera::Setup(const GLfloat _FOV, const GLfloat _width,
	const GLfloat _height,
	const GLfloat _znear, const GLfloat _zfar)
{
	FOV = _FOV; viewWidth = _width; viewHeight = _height;
	znear = _znear; zfar = _zfar;

	glm::vec3 pos = { -1.0f, 0.0f, 2.0f };
	//glm::vec3 front = { 0.0f, 0.0f, 1.0f };
	viewMatrix = glm::lookAt(pos, pos + Target, glm::vec3(0.0f, 1.0f, 0.0f));
	projectionMatrix = glm::perspective(FOV, viewWidth / viewHeight,
		znear, zfar);
	orthoMatrix = glm::ortho<GLfloat>(0, viewWidth, 0, viewHeight);

	transform.modelMatrix = viewMatrix * projectionMatrix;
}

void GreenCow::OpenGL4Camera::LookAt(const glm::vec3 target)
{

}

void GreenCow::OpenGL4Camera::Orbit(const glm::vec3 target, const float distance, const float deltaRad)
{
	glm::vec3 dist = glm::normalize(transform.Position - target) * distance;
	glm::quat orbit = glm::quat(transform.rotationMatrix);
	//transform.AddRotation() 
}
void GreenCow::OpenGL4Camera::Update()
{
	viewMatrix = projectionMatrix = glm::mat4(1.0f);

	glm::vec3 pos = { -1.0f, 0.0f, 2.0f };
	//glm::vec3 front = { 0.0f, 0.0f, 1.0f };
	viewMatrix = glm::lookAt(pos, pos + Target, glm::vec3(0.0f, 1.0f, 0.0f));
	projectionMatrix = glm::perspective(FOV, viewWidth / viewHeight,
		znear, zfar);
	//orthoMatrix = glm::ortho<GLfloat>(0, viewWidth, 0, viewHeight);

	//transform.modelMatrix = viewMatrix * projectionMatrix;
}