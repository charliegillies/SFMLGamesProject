#pragma once
#include <string>
#include <map>
#include <SFML/Graphics/Font.hpp>

class FontLoader
{
private:
	// map holds the string (filepath) and the loaded item
	std::map<std::string, sf::Font> fileMap;
	// checks if an item has been loaded into the map
	bool loaded(std::string fp);

protected:
	sf::Font& loadAsset(const std::string fp);

	sf::Font& put(const std::string fp, sf::Font value);

public:
	FontLoader() : fileMap() {}
	~FontLoader() {}

	// gets the asset from the specific filepath
	sf::Font& get(const std::string fp);
};

