#pragma once

class Game;

/*
	An object that describes the 'scene', which is the current
	state of the game that is running on the screen.
*/
class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}

	// called at the beginning of the scene, only once
	virtual void onStart() = 0;

	// called when the scene has been changed and this scene has stopped
	virtual void onExit() = 0;

	// logic update, called every frame during the scenes lifetime
	virtual void onUpdate() = 0;

	// render update, called every frame during the scenes lifetime
	virtual void onRender() = 0;

	// called by the Game itself when the scene becomes the current scene
	void setGame(Game* game);

protected:
	// changes the current displayed scene
	void changeScene(Scene* scene);
	// todo move to private after scene testing is complete
	Game* _game;


private:

};