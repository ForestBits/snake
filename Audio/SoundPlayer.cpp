#include <cassert>
#include "SoundPlayer.h"



SoundPlayer::SoundPlayer(Resource & resource, float volume) : globalVolume(1)
{
	setVolume(volume);

	sounds[static_cast<int> (Sounds::CLICK_SOUND)].setBuffer(resource.getClickSoundBuffer());
	sounds[static_cast<int> (Sounds::FOOD_SOUND)].setBuffer(resource.getFoodSoundBuffer());
	sounds[static_cast<int> (Sounds::DEATH_SOUND)].setBuffer(resource.getDeathSoundBuffer());
	sounds[static_cast<int> (Sounds::PAUSE_SOUND)].setBuffer(resource.getPauseSoundBuffer());
}

void SoundPlayer::setVolume(float volume)
{
	assert(volume >= 0 && volume <= 1);

	this->volume = volume;

	for (int i = 0; i < static_cast<int> (Sounds::COUNT); ++i)
		sounds[i].setVolume(volume*globalVolume*100);
}

void SoundPlayer::setGlobalVolume(float globalVolume)
{
	assert(globalVolume >= 0 && globalVolume <= 1);

	this->globalVolume = globalVolume;

	for (int i = 0; i < static_cast<int> (Sounds::COUNT); ++i)
		sounds[i].setVolume(volume*globalVolume*100);
}

float SoundPlayer::getVolume() const 
{
	return volume;
}

float SoundPlayer::getGlobalVolume() const
{
	return globalVolume;
}

void SoundPlayer::play(Sounds sound) const
{
	sounds[static_cast<int> (sound)].play();
}