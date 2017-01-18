#pragma once
#include "SceneNode.h"

/*
	This scene node is responsible for destroying its
	active parent after a set amount of time.

	Time is collected via game->deltaTime().
*/
class DestroyAfterTimeNode : public SceneNode
{
public:
	explicit DestroyAfterTimeNode(float destroyTime);
	~DestroyAfterTimeNode();

	void update() override;

private:
	float _destroyTime;
	float _accumulatedTime;
};

