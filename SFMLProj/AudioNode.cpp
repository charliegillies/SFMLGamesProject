#include "AudioNode.h"
#include "Game.h"

AudioNode::AudioNode(AudioPlayMode mode, string fp) 
	: _mode(mode), _fp(fp), _sound() { }
 
AudioNode::~AudioNode() { }

string AudioNode::getNodeTag()
{
	return NodeTag::audio_node;
}

void AudioNode::start()
{
	// Load the sound buffer, create the sound
	sf::SoundBuffer& buffer = getGame()->getSound(_fp);
	_sound.setBuffer(buffer);

	// If we're waiting for trigger, don't play.
	if (_mode != AudioPlayMode::PLAY_ON_TRIGGER)
		_sound.play();

	// If we're playing on repeat, wait.
	if (_mode == AudioPlayMode::PLAY_REPEAT)
		_sound.setLoop(true);
}

void AudioNode::update()
{
	if (_sound.getStatus() == sf::SoundSource::Stopped)
	{
		if (_mode == AudioPlayMode::PLAY_ONCE_DESTROY_SELF)
		{
			auto parent = getParent();
			getGame()->removeSceneNode(parent != nullptr ? parent : this);
		}
	}
}

void AudioNode::trigger()
{
	_sound.play();
}
