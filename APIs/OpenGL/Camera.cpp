#include "Camera.h"

void OpenGL::Camera::Setup(const float _FOV, 
	const float _width,	const float _height,
	const float _znear, const float _zfar)
{
	glm::vec3 pos = { -1.0f, 0.0f, 5.0f };
	viewMatrix = glm::lookAt(pos, pos + Target, Transform::UP);
	SetPerspective(info.FOV, _width / _height,
				   info.zNear, info.zFar);

	orthoMatrix = glm::ortho<GLfloat>(0, _width, 0, _height);

	transform.ModelMatrix = viewMatrix * projectionMatrix;
}

void OpenGL::Camera::LookAt(const glm::vec3 target)
{
	viewMatrix = glm::lookAt(transform.Position, target, Transform::UP);
}

void OpenGL::Camera::SetPerspective(const float fov, const float aspect, const float znear, const float zfar)
{
	info = { fov, aspect, znear, zfar };
	projectionMatrix = info.GetPerspective();
}

void OpenGL::Camera::SetFOV(const float fov)
{
	info.FOV = fov;
	projectionMatrix = info.GetPerspective();
}

void OpenGL::Camera::Orbit(const glm::vec3 target, const float distance, const float deltaRad)
{
	glm::vec3 dist = glm::normalize(transform.Position - target) * distance;
	glm::quat orbit = glm::quat(transform.rotationMatrix);
	//transform.AddRotation() 
}
void OpenGL::Camera::Update()
{
	//viewMatrix = projectionMatrix = glm::mat4(1.0f);

	//glm::vec3 pos = { -1.0f, 0.0f, 2.0f };
	//viewMatrix = glm::lookAt(transform.Position, transform.Position + Target, glm::vec3(0.0f, 1.0f, 0.0f));
	//projectionMatrix = glm::perspective(FOV, viewWidth / viewHeight,
	//	znear, zfar);

	LookAt(transform.Position + Target);

	transform.ModelMatrix = viewMatrix * projectionMatrix;
}