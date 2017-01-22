#pragma once
#include <vector>
#include "SceneNode.h"
#include "Game.h"
#include "EventSystem.h"
#include <queue>

/*
	An object that describes the 'scene', which is the current
	state of the game that is running on the screen.
*/
class Scene
{
public:
	Scene() : _waitingNodes(), _sceneNodes(), _destroyNodes(), _started(false)
	{
		_eventSystem = new EventSystem();
	}

	//todo cleanup
	virtual ~Scene() {}

	// called at the beginning of the scene, only once
	virtual void onStart();

	// called when the scene has been changed and this scene has stopped
	virtual void onExit();

	// logic update, called every frame during the scenes lifetime
	virtual void onUpdate();

	// render update, called every frame during the scenes lifetime
	virtual void onRender();

	// called by the Game itself when the scene becomes the current scene
	void setGame(Game* game);

	// adds a scene node to the current scene
	void addSceneNode(SceneNode* node);

	// removes a node from the scene
	// node param should be the highest node in
	// the hierarchy, as we will not go searching for it.
	void removeSceneNode(SceneNode* node);

	// gets the event system which is specific to the scene
	EventSystem* getEventSystem();

	// searches for a node inside of the scene hierarchy
	SceneNode* searchforNode(string name);

protected:
	// changes the current displayed scene
	void changeScene(Scene* scene);

	// todo move to private after scene testing is complete
	Game* _game;

private:
	// initializes all of the waiting nodes, if any
	void initializeWaiting();
	// destroys all of the nodes that are waiting to be destroyed
	void destroyNodes();

	// these are nodes that were added during a scenes runtime
	queue<SceneNode*> _waitingNodes;
	// the scene nodes that are active in the current scene
	vector<SceneNode*> _sceneNodes;
	// the nodes that need to be destroyed from the hierarchy
	queue<SceneNode*> _destroyNodes;

	// determines if the scene has already been started or not
	bool _started;

	EventSystem* _eventSystem;
};