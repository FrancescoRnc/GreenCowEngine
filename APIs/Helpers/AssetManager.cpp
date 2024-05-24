#include "AssetManager.h"

// AssetContent
unsigned int Helpers::AssetContent::_assetsCount = 0;

const unsigned int Helpers::AssetContent::ID() const 
{ return _id; }

const std::string Helpers::AssetContent::Name() const 
{ return _filepath.stem().string(); };

const std::string Helpers::AssetContent::Extension() const 
{ return _filepath.extension().string(); };

const std::string Helpers::AssetContent::Directory() const 
{ return _filepath.parent_path().string(); };

const size_t Helpers::AssetContent::Size() const 
{ return std::filesystem::file_size(_filepath); };

const std::filesystem::path Helpers::AssetContent::Filepath() const 
{ return _filepath; };

std::unique_ptr<std::vector<std::byte>> Helpers::AssetContent::GetSource() const
{
	auto source = std::make_unique<std::vector<std::byte>>(Size());
	std::ifstream r_file(Filepath());
	r_file.read(reinterpret_cast<char*>(source->data()), Size());
	r_file.close();

	return source;
}


// AssetLoader
Helpers::AssetManager* Helpers::AssetManager::_instance = nullptr;

void Helpers::AssetManager::IterateFolders(std::vector<std::filesystem::path>& found_files, std::filesystem::path iteration)
{
	for (const auto& entry : std::filesystem::directory_iterator(iteration))
	{
		if (entry.is_directory()) 
		{
			IterateFolders(found_files, entry);
		}
		else
		{
			found_files.push_back(entry.path());
		}
	}
}

Helpers::AssetManager* Helpers::AssetManager::Get()
{
	return _instance ? _instance : new AssetManager();
}

void Helpers::AssetManager::LoadFrom(std::filesystem::path folder)
{
	const std::filesystem::path path = std::filesystem::current_path() / folder;
	if (!std::filesystem::exists(path))
	{
		const char* const message = std::string("No folder at [" + path.string() + "] has been found!").c_str();
		throw new std::exception({ message });
	}

	std::vector<std::filesystem::path> foundFiles{};
	IterateFolders(foundFiles, path);

	for (const auto& path : foundFiles)
	{
		AssetContent content = AssetContent(path);

		_assets.insert({ content.Filepath().filename().string(), content});

		//std::cout << "Registered Asset:" << std::endl;
		//std::cout << "Asset Name: " << content.Name() << std::endl;
		//std::cout << "Asset Extension: " << content.Extension() << std::endl;
		//std::cout << "Asset Size: " << content.Size() << std::endl;
		//std::cout << "Asset Directory: " << content.Directory() << std::endl;
		//std::cout << "Asset Path: " << content.Filepath() << std::endl;
		//std::cout << "##################################" << std::endl;
	}
	//std::cout << "Assets Folder: " << GetAssetsFolder() << std::endl;
}

Helpers::AssetContent* Helpers::AssetManager::GetAsset(std::string name)
{
	if (_assets.size() == 0) return nullptr;

	auto found = _assets.find(name);
	if (found != _assets.end())
	{
		return &_assets.at(name);
	}
	return nullptr;
}

const std::filesystem::path Helpers::AssetManager::GetAssetsFolder() const
{
	return std::filesystem::current_path() / ("Assets");
}
