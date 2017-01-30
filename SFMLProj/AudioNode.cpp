#include "AudioNode.h"
#include "Game.h"

AudioNode::AudioNode(AudioPlayMode mode, string fp) 
	: _mode(mode), _fp(fp), _sound() { }
 
AudioNode::~AudioNode() { }

void AudioNode::start()
{
	sf::SoundBuffer& buffer = getGame()->getSound(_fp);
	_sound.setBuffer(buffer);
	_sound.play();

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
