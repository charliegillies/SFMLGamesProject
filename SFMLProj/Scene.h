#pragma once
#include <vector>
#include "SceneNode.h"
#include "Game.h"
#include "EventSystem.h"

/*
	An object that describes the 'scene', which is the current
	state of the game that is running on the screen.
*/
class Scene
{
public:
	Scene() : _sceneNodes()
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

	// gets the event system which is specific to the scene
	EventSystem* getEventSystem();

protected:
	// changes the current displayed scene
	void changeScene(Scene* scene);

	// todo move to private after scene testing is complete
	Game* _game;

private:
	vector<SceneNode*> _sceneNodes;
	EventSystem* _eventSystem;
};