#pragma once
#include <string>
using namespace std;

/*
	Static resource class of Event IDs commonly used in the game.
	Use this to avoid typos and or confusion with IDs - also works
	for project refactoring.
*/
class EventTags
{
public:
	static const string playerLostLife;
	static const string registerCollider;
};