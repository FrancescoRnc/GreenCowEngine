#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include <json/json.h>

namespace Helpers
{
	using json = nlohmann::json;

	struct FileContent
	{
		std::unique_ptr<std::vector<std::byte>> source;
		size_t size = 0;
	};

	struct FileReader
	{
		static FileContent GetFileSource(const std::string filepath)
		{
			FileContent content = {};
			auto path1 = std::filesystem::current_path();
			auto path = std::filesystem::path(filepath);
			content.size = std::filesystem::file_size(path);
			content.source = std::make_unique<std::vector<std::byte>>(content.size);
			std::ifstream r_file(path);
			r_file.read(reinterpret_cast<char*>(content.source->data()), content.size);
			r_file.close();

			return content;
		}

		static json ParseJSON(const std::string jsonFilename)
		{
			std::string text = reinterpret_cast<const char*>(GetFileSource(jsonFilename).source->data());
			json output = json::parse(text);
			return output;
		}
	};
}

