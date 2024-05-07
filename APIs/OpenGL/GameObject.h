#pragma once
#include "../GreenCowEngine.h";
#include "Material.h"
#include "Mesh.h"
#include "Pipeline.h"

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
		GLuint _currentProgram{0};

		public:

		Material* CurrentMaterial{};
		Mesh* CurrentMesh{};
		Transform* WorldTransform;
		

		GameObject()
		{

		}

		GameObject(const GLuint defaultProgram)
		{
			_currentProgram = defaultProgram;
		}

		GameObject(Mesh* mesh, const GLuint defaulProgram)
		{
			CurrentMesh = mesh;
			_currentProgram = defaulProgram;
		}

		GameObject(Mesh* mesh, Material* material)
		{
			CurrentMesh = mesh;
			CurrentMaterial = material;
			_currentProgram = material->GetProgram();
		}

		void Update(const float deltaTime);
		void Draw();
		
		void SetMaterial(Material* mat);

		GameObjectData GetData();

		void Serialize() override;
		GameObjectData Deserialize() override;

		~GameObject()
		{
			//Serialize();
		}
	};

}
