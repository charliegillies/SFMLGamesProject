#include "SfxLoader.h"
#include <SFML/Audio/SoundBuffer.hpp>

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

sf::SoundBuffer& SfxLoader::loadAsset(const std::string fp)
{
	sf::SoundBuffer txr;
	txr.loadFromFile("Content//" + fp);
	return put(fp, txr);
}

sf::SoundBuffer& SfxLoader::put(const std::string fp, sf::SoundBuffer value)
{
	fileMap[fp] = value;
	return fileMap[fp];
}

sf::SoundBuffer& SfxLoader::get(const std::string fp)
{
	// check if we have this asset in the map using the filepath
	// if we do, immediately return it
	if (loaded(fp))
		return fileMap[fp];

	// otherwise, lets load it and return it
	return loadAsset(fp);
}