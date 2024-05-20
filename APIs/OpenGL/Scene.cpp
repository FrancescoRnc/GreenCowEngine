#include "Scene.h"
#include "FileLoader.h"
#include "DataArchivers/GameDataArchiver.h"
#include "../Engine/CameraController.h"

void OpenGL::Scene::Load(const char* scene_filename)
{
	/*if (!scene_filename || scene_filename == "")
		return;

	try
	{
		glm::vec3 vtemp;
		Mesh* mtemp;
		Camera* ctemp;
		std::unordered_map<std::string, std::function<void()>> typeMatcher = {
			{"Camera", [&]() {}},
			{"Mesh", [&]() {}}
		};
		std::unordered_map<std::string, std::function<void(std::stringstream&)>> dataMatcher = {
			{"oname", [&](std::stringstream& stream) {}},
			{"mname", [&](std::stringstream& stream) {}},
			{"tname", [&](std::stringstream& stream) {}},
			{"pos", [&](std::stringstream& stream) {}},
			{"dir", [&](std::stringstream& stream) {}}
		};

		std::stringstream sline;
		std::ifstream stream(scene_filename);
		std::string line = "";
		std::string first_word = "";

		if (!stream.is_open()) return;

		while (std::getline(stream, line))
		{
			sline.clear();
			sline.str(line);
			sline >> first_word;

			auto typematch = typeMatcher.find(first_word);
			if (typematch != typeMatcher.end())
				typematch->second();
		}
	}
	catch (std::exception& ex)
	{
		std::cout << "Error occurred while loading scene file" << std::endl;
		return;
	}*/
}

void OpenGL::Scene::Unload()
{
	GameObjects.clear();
}

void OpenGL::Scene::Init() 
{
	std::vector<Vertex> vertices;
	std::vector<GLint> indices;
	MeshData meshData;

	ActiveCamera->Setup(90, 800, 600, 0.01f, 1000.f);
	ActiveCamera->Target = glm::vec3( 0.0f, 0.0f, 1.0f );
	CameraController::Get()->Possess(ActiveCamera);

	if (!FileLoader::LoadMesh("Assets/Models/Skull.obj", meshData)) {
		return;
	}
	GameDataArchiver::Get()->StoreMesh("skull", meshData);

	GLuint defaultProgram = 1;

	Material mat = { defaultProgram };
	GameDataArchiver::Get()->StoreMaterial("skull", mat);

	Mesh* mesh = new Mesh(GameDataArchiver::Get()->GetMesh("skull"), GameDataArchiver::Get()->GetMaterial("skull"));

	GameObject* go = new GameObject(mesh);
	go->WorldTransform.Translate(glm::vec3(0.0f, 0.0f, 4.0f ));

	GameObjects.push_back(go);
}

void OpenGL::Scene::Update(const float deltaTime)
{
	ActiveCamera->Update();

	for (auto go : GameObjects)
	{
		go->Update(deltaTime);
	}
}