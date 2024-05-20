#pragma once
#include "../Engine/GreenCowEngine.h"

namespace Helpers
{
	struct AssetContent
	{
		unsigned int ID;
		std::string Name;
		size_t Size;
		std::filesystem::path Filepath;

		const char* GetSource() const
		{

		}
	};

	class AssetWrapper
	{
		std::unordered_map<std::string, AssetContent> _assets{};

	public:
		AssetWrapper()
		{			
		}

		AssetWrapper(const std::unordered_map<std::string, AssetContent>& other) : _assets(other)
		{
		}

		void RegisterAssets(const std::unordered_map<std::string, AssetContent> assets);

		inline AssetContent& operator[](std::string key)
		{
			return _assets.at(key);
		}
		inline AssetContent operator[](std::string key) const
		{
			return _assets.at(key);
		}

		~AssetWrapper()
		{
			_assets.clear();
		}
	};

}