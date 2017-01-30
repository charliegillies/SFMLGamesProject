#include "IntroScene.h"
#include "CanvasNode.h"
#include "AnimatedTextNode.h"
#include "LevelOneScene.h"


IntroScene::IntroScene() : _cTime(0.0f) { }
IntroScene::~IntroScene() { }

void IntroScene::onStart()
{
	// Cheesy intro brief!
	string msg = "Captain,\n\n";
	msg += "I will now brief you on project 'Sailor'\n\n";
	msg += "We have captured an enemy warship. Using decoded data we now know\n\n";
	msg += "the location of the alien mothership. Using the captured ship, you are\n\n";
	msg += "being sent to seek and destroy it.\n\n";
	msg += "The captured ship is equipped with basic laser fire (left click),\n";
	msg += "anti-shield missiles (right click) and a rechargeable shield (space).\n\n";
	msg += "Against all odds, you must prevail. Good luck.";

	_canvas = new CanvasNode();

	// Introduction text
	auto intro_text = new AnimatedTextNode(0.048f, 0, 0, 
		"Fonts//kenvector_future_thin.ttf", msg, sf::Color::White, 28);
	_canvas->addChild(intro_text);

	_game->addSceneNode(_canvas);

	// 'Continue' button which shows up after the intro
	_continueTxt = new TextNode(0, 0, "Fonts//kenvector_future.ttf", 
		"Press Start", sf::Color::Yellow, 36);

	// hard coding is fine....right?
	_continueTxt->setPosition(480, 600);

	Scene::onStart();
}

void IntroScene::onUpdate()
{
	const float wait_time = 20.0f;

	_cTime += _game->deltaTime();

	if (_cTime >= wait_time)
	{
		if (_canvas->getChildCount() == 1)
		{
			_canvas->addChild(_continueTxt);
			_continueTxt->start();
		}
	}
	
	if (_game->getInput()->anyKeyDown())
	{
		_game->changeScene(new LevelOneScene());
		return;
	}

	Scene::onUpdate();
}
