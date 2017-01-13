#pragma once
#include "AssetLoader.h"

#include <SFML/Graphics.hpp>

// Texture loader utility that derives from AssetLoader<sf::Texture>
class TextureLoader
{
private:
	// map holds the string (filepath) and the loaded item
	std::map<std::string, sf::Texture> fileMap;
	// checks if an item has been loaded into the map
	bool loaded(std::string fp, sf::Texture& value);

protected:
	virtual void loadAsset(const std::string fp, sf::Texture& value);

	virtual void put(const std::string fp, sf::Texture value);

public:
	TextureLoader() {}
	~TextureLoader();

	// gets the asset from the specific filepath
	void get(const std::string fp, sf::Texture& value);
};