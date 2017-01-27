#include "EventTags.h"
#include <string>
using namespace std;

/*
	List event tags!
*/

const string EventTags::playerLostLife = "plostlife";
const string EventTags::registerCollider = "rcollider";
const string EventTags::unregisterCollider = "urcollider";
const string EventTags::collided = "collided";
const string EventTags::projectileCollision = "pcollision";

const string EventTags::registerEnemy = "renemy";
const string EventTags::unregisterEnemy = "unrenemy";
const string EventTags::playerDeath = "pdeath";