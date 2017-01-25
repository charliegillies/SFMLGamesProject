#include "AnimatedSpriteNode.h"
#include "Game.h"

AnimatedSpriteNode::AnimatedSpriteNode(string filepath, float frame_time, AnimationMode mode)
	: filepath(filepath), frameTime(frame_time), mode(mode), frameQueue() { }

AnimatedSpriteNode::~AnimatedSpriteNode() { }

void AnimatedSpriteNode::start()
{
	transform = static_cast<TransformNode*>(getParent()->getNode(NodeTag::transform_node));

	nextFrameTime = frameTime;

	sf::Texture& txr = getGame()->getTexture(filepath);
	txr.setSmooth(true);
	sprite.setTexture(txr);

	if (frameQueue.size() > 0)
		setupFrame();
}

void AnimatedSpriteNode::update()
{
	// set position, origin, etc.
	sprite.setPosition(transform->position);
	sprite.setRotation(transform->rotation);
	sprite.setOrigin(transform->origin);
	sprite.setScale(transform->scale);

	// ensure there are frames left before running this op
	if (frameQueue.size() == 0) return;

	// count down to the next frame
	nextFrameTime -= getGame()->deltaTime();
	if (nextFrameTime > 0) return;

	// remove current frame
	AnimationFrame& frame = frameQueue.front();
	frameQueue.pop();

	// Handle repeat if necesary
	if (mode == ANIM_REPEAT)
		frameQueue.push(frame);

	// ensure we still have frames left (double check!)
	if (frameQueue.size() == 0) return;

	setupFrame();
	nextFrameTime = frameTime;
}

void AnimatedSpriteNode::render()
{ 
	getGame()->draw(sprite);
}

AnimatedSpriteNode* AnimatedSpriteNode::addFrame(int x, int y, int width, 
	int height, sf::Vector2f origin_multiplier)
{
	frameQueue.push(AnimationFrame(x, y, width, height, origin_multiplier));
	return this;
}

void AnimatedSpriteNode::setupFrame()
{
	AnimationFrame& frame = frameQueue.front();
	sprite.setTextureRect(frame.drawRect);
	
	// set origin..
	sf::Vector2f origin(frame.drawRect.width, frame.drawRect.height);
	origin.x = origin.x * frame.originMultiplier.x;
	origin.y = origin.y * frame.originMultiplier.y;

	transform->origin = origin;
	sprite.setOrigin(transform->origin);
}