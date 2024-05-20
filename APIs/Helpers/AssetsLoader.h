#pragma once
#include "../Engine/GreenCowEngine.h"

namespace Helpers
{
	class AssetsLoader
	{
		//static AssetWrapper _wrapper;

		AssetsLoader()
		{
			//_wrapper = {};
		}

	public:
		static void LoadFrom(std::filesystem::path folder)
		{
			
		}

		//static inline AssetContent& GetAsset(std::string name)
		//{
		//	return _wrapper[name];
		//}

	};
}
