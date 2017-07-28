//plays sounds (as enumerated), and controls their global volume

#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <SFML/Audio.hpp>
#include <array>
#include "../Resource.h"
#include "Sounds.h"

class SoundPlayer
{
	float volume; //[0, 1]
	float globalVolume; //[0, 1]

	mutable std::array<sf::Sound, static_cast<int> (Sounds::COUNT)> sounds;

public:
	//[0, 1]
	SoundPlayer(Resource & resource, float volume); 

	void play(Sounds sound) const;

	//[0, 1]
	void setVolume(float volume); 

	//[0, 1]
	float getVolume() const; 

	//[0, 1]
	void setGlobalVolume(float volume);

	//[0, 1]
	float getGlobalVolume() const;
};


#endif
