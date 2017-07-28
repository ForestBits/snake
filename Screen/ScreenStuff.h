//stuff every screen uses, packed together
//for example, packaging together window, sound

#ifndef SCREENSTUFF_H
#define SCREENSTUFF_H

#include <SFML/Graphics.hpp>
#include "../Audio/SoundPlayer.h"
#include "../Audio/MusicPlayer.h"
#include "TransitionInfo.h"

class ScreenChange;

class ScreenStuff
{
	sf::RenderWindow * window;

	SoundPlayer * soundPlayer;

	MusicPlayer * musicPlayer;
	
	ScreenChange * screenChange;

	TransitionInfo * transitionInfo;

public:
	ScreenStuff();

	void setWindow(sf::RenderWindow & window);
	void setSoundPlayer(SoundPlayer & soundPlayer);
	void setMusicPlayer(MusicPlayer & musicPlayer);
	void setScreenChange(ScreenChange & screenChange);
	void setTransitionInfo(TransitionInfo & transitionInfo);

	sf::RenderWindow & getWindow() const;
	SoundPlayer & getSoundPlayer() const;
	MusicPlayer & getMusicPlayer() const;
	ScreenChange & getScreenChange() const;
	const TransitionInfo & getTransitionInfo() const;
};

#endif



