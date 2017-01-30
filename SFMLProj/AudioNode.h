#pragma once
#include "SceneNode.h"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

enum class AudioPlayMode
{
	PLAY_ONCE_WAIT = 1,
	PLAY_ONCE_DESTROY_SELF = 2,
	PLAY_REPEAT = 3,
	PLAY_ON_TRIGGER = 4,
};

/*
 * Audio node is responsible for playing audio in the scene.
 */
class AudioNode : public SceneNode
{
public:
	AudioNode(AudioPlayMode mode, string fp);
	~AudioNode();

	void start() override;
	void update() override;
	void trigger();
private:
	sf::Sound _sound;
	AudioPlayMode _mode;
	string _fp;
};

