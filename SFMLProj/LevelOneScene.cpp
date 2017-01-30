#include "LevelOneScene.h"
#include "NodeFactory.h"
#include "CollisionHandler.h"
#include "GameStateListener.h"

LevelOneScene::LevelOneScene() { }
LevelOneScene::~LevelOneScene() { }

void LevelOneScene::onStart()
{
	/* This is where we will load all of our pre-defined level 1 actors.
	 * Keep in mind the world is 8x6 cells (1600x1200)
	 */
	// game state listener waits to hear about changes in the world state
	_game->addSceneNode(new GameStateListener());
	// add the collision handler node
	_game->addSceneNode(new CollisionHandler());

	// load standard game background
	_game->addSceneNode(NodeFactory::createBackgroundNode("Sprites//backgrounds//purple.png"));

	// load asteroids
	_game->addSceneNode(NodeFactory::createAsteroid(312, 312));
	_game->addSceneNode(NodeFactory::createAsteroid(150, 220));
	_game->addSceneNode(NodeFactory::createAsteroid(900, 900));
	_game->addSceneNode(NodeFactory::createAsteroid(820, 400));
	_game->addSceneNode(NodeFactory::createAsteroid(200, 1000));
	_game->addSceneNode(NodeFactory::createAsteroid(260, 900));

	// create the player node
	_game->addSceneNode(NodeFactory::createPlayerNode(800, 600));



	Scene::onStart();
}
