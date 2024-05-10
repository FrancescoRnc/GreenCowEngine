#pragma once
#include "../GreenCowEngine.h"

namespace Helpers
{
	struct Asset
	{
		unsigned int ID;
		std::string Name;
		unsigned int Size;
		std::filesystem::path Filepath;

		const char* GetSource() const
		{

		}
	};

	class AssetWrapper
	{
		std::unordered_map<std::string, Asset> _assets{};

	public:
		AssetWrapper()
		{			
		}

		AssetWrapper(const std::unordered_map<std::string, Asset>& other) : _assets(other)
		{
		}

		void RegisterAssets(const std::unordered_map<std::string, Asset> assets);

		inline Asset& operator[](std::string key)
		{
			return _assets.at(key);
		}
		inline Asset operator[](std::string key) const
		{
			return _assets.at(key);
		}

		~AssetWrapper()
		{
			_assets.clear();
		}
	};

}