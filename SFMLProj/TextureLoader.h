#pragma once

#include <SFML/Graphics.hpp>

// Texture loading & caching utility
class TextureLoader
{
private:
	// map holds the string (filepath) and the loaded item
	std::map<std::string, sf::Texture> fileMap;
	// checks if an item has been loaded into the map
	bool loaded(std::string fp);

protected:
	sf::Texture& loadAsset(const std::string fp);

	sf::Texture& put(const std::string fp, sf::Texture value);

public:
	TextureLoader() {}
	~TextureLoader();

	// gets the asset from the specific filepath
	sf::Texture& get(const std::string fp);
};