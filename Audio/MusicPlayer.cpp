#include <cassert>
#include "../Resource.h"
#include "../Exception.h"
#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(float volume) : globalVolume(1)
{
	setVolume(volume);

	if (!musics[static_cast<int> (Musics::MENU_MUSIC)].openFromFile("res/Pamgaea.ogg"))
		throw Exception(Cause::MISSING_MENU_MUSIC);

	if (!musics[static_cast<int> (Musics::GAME_MUSIC)].openFromFile("res/Electrodoodle.ogg"))
		throw Exception(Cause::MISSING_GAME_MUSIC);
}

void MusicPlayer::setVolume(float volume)
{
	assert(volume >= 0 && volume <= 1);

	this->volume = volume;

	for (int i = 0; i < static_cast<int> (Musics::COUNT); ++i)
		musics[i].setVolume(volume*globalVolume*100);
}

float MusicPlayer::getVolume() 
{
	return volume;
}

void MusicPlayer::setGlobalVolume(float volume)
{
	assert(volume >= 0 && volume <= 1);

	globalVolume = volume;

	for (int i = 0; i < static_cast<int> (Musics::COUNT); ++i)
		musics[i].setVolume(this->volume*globalVolume*100);
}

float MusicPlayer::getGlobalVolume()
{
	return globalVolume;
}

void MusicPlayer::play(Musics music)
{
	musics[static_cast<int> (music)].play();
}

void MusicPlayer::pause(Musics music)
{
	musics[static_cast<int> (music)].pause();
}

void MusicPlayer::stop(Musics music)
{
	musics[static_cast<int> (music)].stop();
}

bool MusicPlayer::getLoop(Musics music)
{
	return musics[static_cast<int> (music)].getLoop();
}

float MusicPlayer::getPitch(Musics music)
{
	return musics[static_cast<int> (music)].getPitch();
}

sf::SoundSource::Status MusicPlayer::getStatus(Musics music)
{
	return musics[static_cast<int> (music)].getStatus();
}

void MusicPlayer::setLoop(Musics music, bool loop)
{
	musics[static_cast<int> (music)].setLoop(loop);
}

void MusicPlayer::setPitch(Musics music, float pitch)
{
	musics[static_cast<int> (music)].setPitch(pitch);
}

