#include "Scene.h"
#include "FileLoader.h"

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
	FileLoader loader;
	std::vector<Vertex> vertices;
	std::vector<GLint> indices;

	if (!loader.LoadModel("Assets/Models/model_cow.obj", vertices, indices)) {
		return;
	}

	ActiveCamera->Setup(60, 800, 600, 0.01f, 1000.f);
	ActiveCamera->Target = { 0.0f, 0.0f, 1.0f };

	Mesh* mesh = new Mesh(ActiveCamera);
	mesh->Setup(vertices, indices);
	mesh->transform.Translate({ 0.0f, 0.0f, -4.0f });
	mesh->transform.Rotate({0.0f, 1.0f, 0.0f}, 3.14f / 4);
	mesh->transform.ReScale(glm::vec3(1.0f));
	mesh->Texture = loader.LoadTexture("Assets/Textures/ground.jpg");

	GLuint defaultProgram = refPipeline->DefaultProgram();
	//Helpers::SerializedDataRetriever::GetDefaultProgram(defaultProgram);

	GameObjects.push_back(new GameObject(mesh, defaultProgram));
}

void OpenGL::Scene::Update(const float deltaTime)
{
	ActiveCamera->Update();

	for (auto go : GameObjects)
	{
		go->Update(deltaTime);
	}
}

void OpenGL::Scene::Draw()
{
	for (auto go : GameObjects)
	{
		go->Draw();
	}
}