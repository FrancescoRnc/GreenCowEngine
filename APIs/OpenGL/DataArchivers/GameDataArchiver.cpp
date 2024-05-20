#include "GameDataArchiver.h"
#include "../Mesh.h"

template<typename T>
void OpenGL::DataArchiver<T>::Store(std::string id, T obj)
{
	auto found = _storedObjects.find(id);
	if (found == _storedObjects.end())
	{
		_storedObjects.insert({id, obj});
	}
}

template<typename T>
T* OpenGL::DataArchiver<T>::Get(std::string id)
{
	auto found = _storedObjects.find(id);
	if (found != _storedObjects.end())
	{
		return &_storedObjects.at(id);
	}
	return nullptr;
}

OpenGL::GameDataArchiver::GameDataArchiver()
{
	meshes = {};
	textures = {};
	materials = {};
	shaders = {};
}

void OpenGL::GameDataArchiver::StoreMesh(std::string name, MeshData mesh) { meshes.Store(name, mesh); }
OpenGL::MeshData* OpenGL::GameDataArchiver::GetMesh(std::string name) { return meshes.Get(name); }

void OpenGL::GameDataArchiver::StoreTexture(std::string name, Texture texture) { textures.Store(name, texture); }
OpenGL::Texture* OpenGL::GameDataArchiver::GetTexture(std::string name) { return textures.Get(name); }

void OpenGL::GameDataArchiver::StoreMaterial(std::string name, Material material) { materials.Store(name, material); }
OpenGL::Material* OpenGL::GameDataArchiver::GetMaterial(std::string name) { return materials.Get(name); }

void OpenGL::GameDataArchiver::StoreShader(std::string name, Shader shader) { shaders.Store(name, shader); }
OpenGL::Shader* OpenGL::GameDataArchiver::GetShader(std::string name) { return shaders.Get(name); }

OpenGL::GameDataArchiver* OpenGL::GameDataArchiver::_instance = nullptr;