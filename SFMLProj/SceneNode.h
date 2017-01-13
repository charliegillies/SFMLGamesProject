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
	SceneNode* addChild(SceneNode* node);

	// this is where the initialization behaviour of the scene node starts
	virtual void start();

	// updates the scene node, can be overriden 
	virtual void update();

	// allows the scene node to render
	virtual void render();

	// gets the parent of this scene node
	SceneNode* getParent();

	// sets the parent node of the scene node
	// this should happen automatically on addChild(*node)
	void setParent(SceneNode* parent);

	// sets the game object inside of the scene node
	void setGame(Game* game);

protected:
	Game* getGame();

private:
	std::vector<SceneNode*> _childNodes;
	SceneNode* _parent;
	Game* _game;
};

