#include "AssetLoader.h"

template <class T>
void AssetLoader<T>::get(std::string fp, T& value)
{
	// loaded(fp, value) will fill the value if it is loaded
	// otherwise, we ask the overrided loadAsset() method to load it
	if (!loaded(fp, value))
		loadAsset(fp, value);
}

template <class T>
bool AssetLoader<T>::loaded(std::string fp, T& value)
{
	// attempt to find an item with this key
	auto iterator = _fileMap.find(fp);

	// compare to end to see if the iterator succeeded
	// if it did, assign value to the found item
	if (iterator != _fileMap.end())
	{
		value = iterator->second;
		return true;
	}

	return false;
}
