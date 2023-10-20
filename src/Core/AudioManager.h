#pragma once

#include <irrKlang.h>
#include <string>
#define AUDIO AudioManager::GetInstance()

class AudioManager
{
	irrklang::ISoundEngine* _soundtrack = irrklang::createIrrKlangDevice();
	irrklang::ISoundEngine* _effects = irrklang::createIrrKlangDevice();
	AudioManager();
public:

	static AudioManager GetInstance();
	void setUp(float musicVolume, float effectVolume);
	void playMusic(std::string path, bool isLooped = false);
	void playEffect(std::string path, float volume = 1.f, float speed = 1);
	void pauseEffect();
	void pauseMusic();
	float getSoundVolume();
	float getEffectsVolume();
	void setSoundVolume(float value);
	void setEffectsVolume(float value);
	void removeAudio();
	float clamp(float min, float value, float max);
};