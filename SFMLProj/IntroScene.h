#pragma once
#include "Scene.h"
#include "TextNode.h"

/*
 *	Scene which is the introduction to the game.
 */
class IntroScene : public Scene
{
public:
	IntroScene();
	~IntroScene();

	void onStart() override;
	void onUpdate() override;

private:
	SceneNode* _canvas;
	TextNode* _continueTxt;
	float _cTime;
};

