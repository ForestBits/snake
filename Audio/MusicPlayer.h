//global volume control for music, as well as allowing play, pause, stop, and start controls for enumerated music

#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <SFML/Audio.hpp>
#include <array>
#include "../Resource.h"
#include "Musics.h"

class MusicPlayer
{
	float volume; //[0, 1]
	float globalVolume; //[0, 1]

	std::array<sf::Music, static_cast<int> (Musics::COUNT)> musics;

public:
	//throws Exception, volume [0, 1]
	MusicPlayer(float volume); 

	void play(Musics music);

	void stop(Musics music);

	void pause(Musics music);

	sf::SoundSource::Status getStatus(Musics music);

	bool getLoop(Musics music);

	float getPitch(Musics music);

	void setLoop(Musics music, bool loop);

	void setPitch(Musics music, float pitch);

	//[0, 1]
	void setVolume(float volume);

	//[0, 1]
	float getVolume();

	//[0, 1]
	void setGlobalVolume(float volume);

	//[0, 1]
	float getGlobalVolume();
};

#endif
