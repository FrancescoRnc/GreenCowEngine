#pragma once
#include "../Engine/GreenCowEngine.h"
#include "Material.h"
#include "Mesh.h"
//#include "Pipeline.h"

namespace OpenGL
{
	// Used for Serialization
	struct GameObjectData
	{
		uint32_t MeshID;
		uint32_t MaterialID;
		glm::vec3 Position;
		glm::vec3 Rotation;
	};

	class GameObject : ISerializable<GameObjectData>
	{
	public:

		Mesh* CurrentMesh{};
		Transform WorldTransform;


		GameObject()
		{

		}

		GameObject(Mesh* mesh)
		{
			CurrentMesh = mesh;
		}

		void Update(const float deltatime);

		GameObjectData GetData();

		void Serialize() override;
		GameObjectData Deserialize() override;

		~GameObject()
		{
			//Serialize();
		}
	};

}
