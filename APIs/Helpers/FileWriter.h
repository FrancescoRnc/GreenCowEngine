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

	struct FileWriter
	{
		static bool SaveFile(const std::string filename, std::string contentText)
		{
			std::ofstream file;
			file.open(filename);
			file << contentText;
			file.close();

			return true;
		}
	};
}

