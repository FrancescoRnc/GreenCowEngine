#pragma once
#include "../../Engine/GreenCowEngine.h"

namespace OpenGL
{
	struct MeshData;
	class Texture;
	class Material;
	struct Shader;

	template<typename T>
	class DataArchiver 
	{
	protected:
		std::unordered_map<std::string, T> _storedObjects;
	public:
		void Store(std::string id, T obj);
		T* Get(std::string id);
	};

	class GameDataArchiver
	{
		static GameDataArchiver* _instance;

		DataArchiver<MeshData> meshes{};
		DataArchiver<Texture> textures{};
		DataArchiver<Material> materials{};
		DataArchiver<Shader> shaders{};

	public:
		GameDataArchiver();

		inline static GameDataArchiver* Get()
		{
			if (!_instance) _instance = new GameDataArchiver();
			return _instance;
		}

		void StoreMesh(std::string name, MeshData mesh);
		MeshData* GetMesh(std::string name);

		void StoreTexture(std::string name, Texture texture);
		Texture* GetTexture(std::string name);

		void StoreMaterial(std::string name, Material material);
		Material* GetMaterial(std::string name);

		void StoreShader(std::string name, Shader shader);
		Shader* GetShader(std::string name);
	};
	
}
