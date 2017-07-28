//basically just putting together the two to pass through the rooms

#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "MusicPlayer.h"
#include "SoundPlayer.h"

struct AudioPlayer
{
	MusicPlayer musicPlayer;
	SoundPlayer soundPlayer;
};

#endif

