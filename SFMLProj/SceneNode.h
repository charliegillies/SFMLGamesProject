#pragma once
#include <vector>

class Game;

/*
	A scene node is an object in the world.
	It can be composite or behavioural object.
*/
class SceneNode
{
public:
	SceneNode();
	virtual ~SceneNode();

	// adds a child to the internal list of child nodes
	void addChild(SceneNode* node);

	// updates the scene node, can be overriden 
	virtual void update();

	// allows the scene node to render
	virtual void render(Game* game);

	// gets the parent of this scene node
	SceneNode* getParent();

	// sets the parent node of the scene node
	// this should happen automatically on addChild(*node)
	void setParent(SceneNode* parent);

private:
	std::vector<SceneNode*> _childNodes;
	SceneNode* _parent;
};

