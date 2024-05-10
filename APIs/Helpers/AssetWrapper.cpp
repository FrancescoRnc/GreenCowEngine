#include "AssetWrapper.h"

void Helpers::AssetWrapper::RegisterAssets(const std::unordered_map<std::string, Asset> assets)
{
	for (auto asset : assets)
	{
		auto find = _assets.find(asset.first);
		if (find == _assets.end())
		{
			_assets.insert({ asset.first, asset.second });
		}
	}
}