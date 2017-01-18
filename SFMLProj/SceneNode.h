#pragma once
#include <vector>
#include "NodeTag.h"
#include "assert.h"
#include "BaseEvent.h"
#include "Delegate.h"
#include "EventSystem.h"

class EventReceiver;
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

	// if this scene node has or has not been removed
	bool waitingRemoval()
	{
		return (getParent() != nullptr) ? getParent()->_removed : _removed;
	}

	// adds a child to the internal list of child nodes
	SceneNode* addChild(SceneNode* node);

	// this is where the node will subscribe to events if 
	// that is in the nodes specific behaviour.
	// this method is invoked before start()
	virtual void subscribeEvents();

	// this is where the initialization behaviour of the scene node starts
	virtual void start();

	// updates the scene node, can be overriden 
	virtual void update();

	// allows the scene node to render
	virtual void render();

	// called by the parent scene node after removed() has been called.
	virtual void onRemoved();

	// called when the scene removes the node from it's hierarchy
	void remove();

	// gets the parent of this scene node
	SceneNode* getParent();

	// sets the parent node of the scene node
	// this should happen automatically on addChild(*node)
	void setParent(SceneNode* parent);

	// sets the game object inside of the scene node
	void setGame(Game* game);

	// gets the node tag that is specific to the node type
	// you can see these node tags in the NodeTag class.
	virtual string getNodeTag();

	// gets a child node by the given tag parameter
	// view the set parameters in the NodeTag class.
	SceneNode* getNode(string tag);

protected:
	Game* getGame();

	// creates an event receiver that is unique to the scene
	EventReceiver* subGlobalEvent(const string id, Gallant::Delegate1<BaseEvent*> del);
	// invokes a global event for all listening receivers
	void invokeGlobalEvent(const string id, BaseEvent* param);

	// creates an event receiver that is unique to the ultimate parent node
	EventReceiver* subLocalEvent(const string id, Gallant::Delegate1<BaseEvent*> del);
	// invokes a local event for all listening receivers
	void invokeLocalEvent(const string id, BaseEvent* param);

private:
	EventSystem _localEventSys;
	vector<SceneNode*> _childNodes;
	SceneNode* _parent;
	Game* _game;
	bool _removed;
};

