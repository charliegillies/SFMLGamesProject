#include "TextureLoader.h"

TextureLoader::~TextureLoader() {}

bool TextureLoader::loaded(const std::string fp)
{
	// attempt to find an item with this key
	auto iterator = fileMap.find(fp);

	// compare to end to see if the iterator succeeded
	return iterator != fileMap.end();
}

sf::Texture& TextureLoader::loadAsset(const std::string fp)
{
	sf::Texture txr;
	txr.loadFromFile("Content//" + fp);
	return put(fp, txr);
}

sf::Texture& TextureLoader::put(const std::string fp, sf::Texture value)
{
	fileMap[fp] = value;
	return fileMap[fp];
}

sf::Texture& TextureLoader::get(const std::string fp)
{
	// check if we have this asset in the map using the filepath
	// if we do, immediately return it
	if (loaded(fp))
		return fileMap[fp];
	
	// otherwise, lets load it and return it
	return loadAsset(fp);
}