#pragma once
#include <string>
#include <map>
#include <SFML/Audio/Sound.hpp>

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
	std::map<std::string, sf::SoundBuffer> fileMap;
	// checks if an item has been loaded into the map
	bool loaded(std::string fp);

protected:
	sf::SoundBuffer& loadAsset(const std::string fp);

	sf::SoundBuffer& put(const std::string fp, sf::SoundBuffer value);

public:
	// gets the asset from the specific filepath
	sf::SoundBuffer& get(const std::string fp);
};

