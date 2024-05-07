#include "GameObject.h"


void OpenGL::GameObject::Update(const float deltaTime)
{

}

void OpenGL::GameObject::Draw()
{
	CurrentMesh->Draw(_currentProgram);
}

void OpenGL::GameObject::SetMaterial(Material* mat)
{
	CurrentMaterial = mat;
	_currentProgram = mat->GetProgram();
}

OpenGL::GameObjectData OpenGL::GameObject::GetData()
{
	return {
		//0,
		//0,
		//WorldTransform->Position(),
		//WorldTransform->Rotation()
	};
}

void OpenGL::GameObject::Serialize()
{

}

OpenGL::GameObjectData OpenGL::GameObject::Deserialize()
{
	return GameObjectData();
}
