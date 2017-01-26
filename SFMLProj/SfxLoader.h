#pragma once
#include <string>
#include <map>

namespace sf{
	typedef int Sound;
}

/*
	Sound effect loading pipeline.
*/
class SfxLoader
{
public:
	SfxLoader();
	~SfxLoader();

private:
	// map holds the string (filepath) and the loaded item
	std::map<std::string, sf::Sound> fileMap;
	// checks if an item has been loaded into the map
	bool loaded(std::string fp);

protected:
	sf::Sound& loadAsset(const std::string fp);

	sf::Sound& put(const std::string fp, sf::Sound value);

public:
	// gets the asset from the specific filepath
	sf::Sound& get(const std::string fp);
};

