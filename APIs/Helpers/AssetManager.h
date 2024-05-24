#pragma once
#include "../Engine/GreenCowEngine.h"
#include "AssetLoader.h"

namespace Helpers
{
	struct AssetContent
	{
		AssetContent()
		{
		}

		AssetContent(const std::filesystem::path path) : _filepath(path)
		{
			_assetsCount++;
			_id = _assetsCount;
		}

		const unsigned int ID() const;
		const std::string Name() const;
		const std::string Extension() const;
		const std::string Directory() const;
		const size_t Size() const;
		const std::filesystem::path Filepath() const;

		std::unique_ptr<std::vector<std::byte>> GetSource() const;

	private:
		static unsigned int _assetsCount;
		unsigned int _id{ 0 };
		std::filesystem::path _filepath{ "" };
	};

	class AssetManager
	{
		static AssetManager* _instance;

		std::unordered_map<std::string, AssetContent> _assets{};

		void IterateFolders(std::vector<std::filesystem::path>& found_files, std::filesystem::path iteration);
		
		
	public:
		AssetManager() : _assets({})
		{
			_instance = this;
		}

		~AssetManager()
		{
			_assets.clear();
		}

		static AssetManager* Get();

		void LoadFrom(std::filesystem::path folder);

		AssetContent* GetAsset(std::string name);
		const std::filesystem::path GetAssetsFolder() const;

	};
}
