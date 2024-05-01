#include "OpenGL4Scene.h"

void GreenCow::OpenGL4Scene::Load(const char* scene_filename)
{
	if (!scene_filename || sizeof(scene_filename) == 0)
		return;
	try
	{
		glm::vec3 vtemp;
		OpenGL4Mesh* mtemp;
		OpenGL4Camera* ctemp;
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
	}
}

void GreenCow::OpenGL4Scene::Unload()
{
	Meshes.clear();
	delete refCamera;
}

void GreenCow::OpenGL4Scene::Update(const float deltaTime)
{

}

void GreenCow::OpenGL4Scene::Draw()
{

}