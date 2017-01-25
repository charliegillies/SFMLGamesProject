#pragma once
#include "SceneNode.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <queue>
#include "TransformNode.h"

struct AnimationFrame
{
	AnimationFrame(int x, int y, int width, int height, sf::Vector2f origin_multiplier)
		: drawRect(x, y, width, height), originMultiplier(origin_multiplier) { }

	sf::IntRect drawRect;
	sf::Vector2f originMultiplier;
};

enum AnimationMode
{
	ANIM_REPEAT = 1,
	ANIM_PLAY_ONCE = 2
};

/*
	Sprite animation node.
*/
class AnimatedSpriteNode : public SceneNode
{
public:
	AnimatedSpriteNode(string filepath, float frame_time, AnimationMode mode);
	~AnimatedSpriteNode();

	void start() override;
	void update() override;
	void render() override;

	AnimatedSpriteNode* addFrame(int x, int y, int width, int height, sf::Vector2f origin_multiplier);

private:
	void setupFrame();

	TransformNode* transform;

	string filepath;

	float frameTime;
	float nextFrameTime;

	AnimationMode mode;
	sf::Sprite sprite;
	queue<AnimationFrame> frameQueue;
};
