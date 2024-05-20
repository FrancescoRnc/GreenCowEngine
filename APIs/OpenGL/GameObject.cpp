#include "GameObject.h"


void OpenGL::GameObject::Update(const float deltatime)
{
	WorldTransform.AddRotation(glm::vec3(0.0f, 1.0f, 0.0f), 5.f * deltatime);

	CurrentMesh->ModelMatrix = WorldTransform.GetModel();

	//WorldTransform.up = WorldTransform.Up();
	//WorldTransform.right = WorldTransform.Right();
	//WorldTransform.forward = WorldTransform.Forward();
}

OpenGL::GameObjectData OpenGL::GameObject::GetData()
{
	return {
		0,
		0,
		WorldTransform.Position,
		WorldTransform.Rotation
	};
}

void OpenGL::GameObject::Serialize()
{

}

OpenGL::GameObjectData OpenGL::GameObject::Deserialize()
{
	return GameObjectData();
}
