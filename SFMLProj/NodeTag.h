#pragma once
#include <string>
using namespace std;

/*
	Static resource class of Node IDs commonly used in the game.
	Use this to avoid typos and or confusion with IDs - also works
	for project refactoring.
*/
class NodeTag
{
public:
	static const string powerup_node;
	static const string empty_node;
	static const string transform_node;
	static const string sprite_node;
	static const string collision_node;
	static const string projectile_data_node;
	static const string health_node;
	static const string audio_node;
};