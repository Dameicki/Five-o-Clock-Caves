#include <Core/AudioManager.h>
#include <iostream>

AudioManager::AudioManager()
{

}

AudioManager AudioManager::GetInstance()
{
	static AudioManager* instance = NULL;
	if (instance == NULL)
	{
		instance = new AudioManager();
	}
	return *instance;
}

void AudioManager::setUp(float musicVolume, float effectVolume)
{
	_soundtrack->setSoundVolume(musicVolume);
	_effects->setSoundVolume(effectVolume);
}

void AudioManager::playMusic(std::string path, bool isLooped)
{
	_soundtrack->play2D(path.c_str(), isLooped);
}

void AudioManager::playEffect(std::string path, float volume, float speed)
{
	irrklang::ISound* effect;
	effect = _effects->play2D(path.c_str(), false, true);
	if (effect)
	{
		effect->setVolume(volume);
		effect->setPlaybackSpeed(speed);
	}
	effect->setIsPaused(false);
	effect->drop();
}

void AudioManager::pauseEffect()
{
	_effects->stopAllSounds();
}

void AudioManager::pauseMusic()
{
	_soundtrack->stopAllSounds();
}

float AudioManager::getSoundVolume()
{
	return _soundtrack->getSoundVolume();
}

float AudioManager::getEffectsVolume()
{
	return _effects->getSoundVolume();
}

void AudioManager::setSoundVolume(float value)
{
	_soundtrack->setSoundVolume(clamp(0, value, 1));
}

void AudioManager::setEffectsVolume(float value)
{
	_effects->setSoundVolume(clamp(0, value, 1));
}

void AudioManager::removeAudio()
{
	_soundtrack->drop();
	_effects->drop();
}

float AudioManager::clamp(float min, float value, float max)
{
	if (value > min && value < max) return value;
	else if (value <= min) return min;
	else if (value >= max) return max;
}

