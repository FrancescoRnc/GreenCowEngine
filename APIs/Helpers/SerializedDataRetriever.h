#pragma once
#include "../Engine/GreenCowEngine.h"

namespace Helpers
{
#define SHADER_PROGRAMS "ShaderPrograms.csv"

	#define ProgramMap std::unordered_map<std::string, uint32_t>
	

	class SerializedDataRetriever
	{
		static const std::string _serializedDataPath;

		static char* getSerializedFile(std::string filename)
		{
			FileContent content = FileReader::GetFileSource(_serializedDataPath + filename);
			return reinterpret_cast<char*>(content.source->data());
		}

		public: 
		SerializedDataRetriever()
		{

		}
		//static Pipeline* refPipeline;

		static bool GetDefaultProgram(GLuint& outputProgram)
		{
			return GetProgramByName("default", outputProgram);
		}

		static bool GetProgramByName(std::string programName, GLuint& outputProgram)
		{
			json json = FileReader::ParseJSON(_serializedDataPath + SHADER_PROGRAMS);
			auto h = json[programName].template get<uint32_t>();

			return true;
		}

		static bool SerializePrograms(ProgramMap programs)
		{
			json obj;
			for (auto prog : programs)
			{
				obj[prog.first] = "" + prog.second;
			}
			FileWriter::SaveFile(_serializedDataPath + SHADER_PROGRAMS, obj.dump());

			return true;
		}

		static bool EmptySerializedData()
		{
			return false;
		}

		~SerializedDataRetriever()
		{
			// Empty ShaderPrograms file
			EmptySerializedData();
		}
	};

	
}

