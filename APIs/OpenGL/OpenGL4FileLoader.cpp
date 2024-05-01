#include "OpenGL4FileLoader.h"
#include <stdexcept>

bool GreenCow::OpenGL4FileLoader::LoadModel(std::string filepath,
	std::vector<Vertex>& out_vertices,
	std::vector<GLint>& out_indices)
{
	std::cout << "Loading file at: " << filepath << std::endl;

	std::vector<glm::vec3> vertices_positions;
	std::vector<glm::vec2> vertices_texcoords;
	std::vector<glm::vec3> vertices_normals;
	std::vector<GLint> indices_positions;
	std::vector<GLint> indices_texcoords;
	std::vector<GLint> indices_normals;
	std::vector<Vertex> vertices;

	std::stringstream sline;
	std::ifstream stream(filepath);
	//std::stringstream ss;
	std::string line = "";
	std::string prefix = "";

	std::vector<std::vector<GLint>*> indices_refs = { &indices_positions, &indices_texcoords, &indices_normals };
	std::unordered_map<std::string, std::function<void(std::stringstream&)>> prefix_matcher = {
		{"v",  [&](std::stringstream& stream)
		{
			 glm::vec3 temp;
			 stream >> temp.x >> temp.y >> temp.z;
			 vertices_positions.push_back(temp);
		}},
		{"vt", [&](std::stringstream& stream)
		{
			glm::vec2 temp;
			stream >> temp.x >> temp.y;
			vertices_texcoords.push_back(temp);
		}},
		{"vn", [&](std::stringstream& stream)
		{
			glm::vec3 temp;
			stream >> temp.x >> temp.y >> temp.z;
			vertices_normals.push_back(temp);
		}},
		{"f",  [&](std::stringstream& stream)
		{
			std::array<std::string, 3> indices;
			stream >> indices[0] >> indices[1] >> indices[2];
			for (auto i : indices)
			{
				std::stringstream sstream(i);
				std::string temp;
				for (size_t i = 0; std::getline(sstream, temp, '/'); i++)
				{
					GLint value = std::stoi(temp);
					indices_refs[i]->push_back(value);
				}
			}
		}}
	};

	if (!stream.is_open()) return false;

	while (std::getline(stream, line))
	{
		sline.clear();
		sline.str(line);
		sline >> prefix;

		auto match = prefix_matcher.find(prefix);
		if (match != prefix_matcher.end())
			match->second(sline);

	}

	vertices.resize(indices_positions.size(), Vertex());
	size_t size = vertices.size();
	for (size_t i = 0; i < size; i++)
	{
		vertices[i].position = vertices_positions[indices_positions[i] - 1];
		vertices[i].texCoords = vertices_texcoords[indices_texcoords[i] - 1];
		if (vertices_normals.size() > 0)
			vertices[i].normal = vertices_normals[indices_normals[i] - 1];
	}

	std::cout << "Total vertices: " << vertices.size() << std::endl;
	std::cout << "Total position indices: " << indices_positions.size() << std::endl;
	std::cout << "Total texcoord indices: " << indices_texcoords.size() << std::endl;
	std::cout << "Total normal indices: " << indices_normals.size() << std::endl;

	out_vertices = vertices;
	out_indices = indices_positions;

	return true;
}

GLuint GreenCow::OpenGL4FileLoader::LoadTexture(std::string filepath)
{
	GLuint texId;

	int width, height, channels;
	auto image = stbi_load(filepath.c_str(), &width, &height, &channels, STBI_rgb);
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D,
		0, GL_RGB, width, height,
		0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	return texId;
}