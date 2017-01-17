#include "CanvasNode.h"
#include "Game.h"

CanvasNode::CanvasNode() {}
CanvasNode::~CanvasNode() {}

void CanvasNode::update()
{
	// switch to ui view
	getGame()->getCamera()->switchToUIView();

	// call update function to avoid mis-translated coordinates
	SceneNode::update();

	// switch back to game view for the other actors
	getGame()->getCamera()->switchToGameView();
}

void CanvasNode::render()
{
	// switch to ui view
	getGame()->getCamera()->switchToUIView();

	// call base render function to render all children
	SceneNode::render();

	// switch back to game view for the other actors
	getGame()->getCamera()->switchToGameView();
}