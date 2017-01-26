#include "SfxLoader.h"


SfxLoader::SfxLoader()
{
}


SfxLoader::~SfxLoader()
{
}

bool SfxLoader::loaded(const std::string fp)
{
	// attempt to find an item with this key
	auto iterator = fileMap.find(fp);

	// compare to end to see if the iterator succeeded
	return iterator != fileMap.end();
}

sf::Sound& SfxLoader::loadAsset(const std::string fp)
{
	sf::Sound txr;
	//txr.loadFromFile("Content//" + fp);
	return put(fp, txr);
}

sf::Sound& SfxLoader::put(const std::string fp, sf::Sound value)
{
	fileMap[fp] = value;
	return fileMap[fp];
}

sf::Sound& SfxLoader::get(const std::string fp)
{
	// check if we have this asset in the map using the filepath
	// if we do, immediately return it
	if (loaded(fp))
		return fileMap[fp];

	// otherwise, lets load it and return it
	return loadAsset(fp);
}