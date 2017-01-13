#include "TextureLoader.h"
#include <assert.h>

TextureLoader::~TextureLoader() {}

bool TextureLoader::loaded(const std::string fp, sf::Texture& value)
{
	// attempt to find an item with this key
	auto iterator = fileMap.find(fp);

	// compare to end to see if the iterator succeeded
	// if it did, assign value to the found item
	if (iterator != fileMap.end())
	{
		value = iterator->second;
		return true;
	}

	return false;
}

void TextureLoader::loadAsset(const std::string fp, sf::Texture& value)
{
	sf::Texture txr;
	bool loaded = txr.loadFromFile("Content//" + fp);
	// handle loading failure here..

	put(fp, txr);
}

void TextureLoader::put(const std::string fp, sf::Texture value)
{
	fileMap[fp] = value;
}

void TextureLoader::get(const std::string fp, sf::Texture& value)
{
	// loaded(fp, value) will fill the value if it is loaded
	// otherwise, we ask the overrided loadAsset() method to load it
	if (!loaded(fp, value))
		loadAsset(fp, value);
}