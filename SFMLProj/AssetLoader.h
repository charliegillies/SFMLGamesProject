#pragma once
#include <string>
#include <map>

template<class T>
class AssetLoader
{
public:
	AssetLoader() {}
	virtual ~AssetLoader() {}

	// gets the asset from the specific filepath
	void get(std::string fp, T& value);

protected:
	// called internally by the AssetLoader for asset specific loading
	virtual void loadAsset(std::string fp, T& value) = 0;

private:
	// map holds the string (filepath) and the loaded item
	std::map<std::string, T>;
	// checks if an item has been loaded into the map
	bool loaded(std::string fp);
};