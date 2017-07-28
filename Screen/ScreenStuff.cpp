#include <cassert>
#include "ScreenStuff.h"
#include "ScreenChange.h"
#include "../Resource.h"

ScreenStuff::ScreenStuff() : window(nullptr), soundPlayer(nullptr), musicPlayer(nullptr), screenChange(nullptr), transitionInfo(nullptr) {}

void ScreenStuff::setWindow(sf::RenderWindow & window)
{
	this->window = &window;
}

void ScreenStuff::setSoundPlayer(SoundPlayer & soundPlayer)
{
	this->soundPlayer = &soundPlayer;
}

void ScreenStuff::setMusicPlayer(MusicPlayer & musicPlayer)
{
	this->musicPlayer = &musicPlayer;
}

void ScreenStuff::setScreenChange(ScreenChange & screenChange)
{
	this->screenChange = &screenChange;
}

void ScreenStuff::setTransitionInfo(TransitionInfo & transitionInfo)
{
	this->transitionInfo = &transitionInfo;
}

sf::RenderWindow & ScreenStuff::getWindow() const
{
	assert(window != nullptr);

	return *window;
}

SoundPlayer & ScreenStuff::getSoundPlayer() const
{
	assert(soundPlayer != nullptr);

	return *soundPlayer;
}

MusicPlayer & ScreenStuff::getMusicPlayer() const
{
	assert(musicPlayer != nullptr);

	return *musicPlayer;
}

ScreenChange & ScreenStuff::getScreenChange() const
{
	assert(screenChange != nullptr);

	return *screenChange;
}

const TransitionInfo & ScreenStuff::getTransitionInfo() const
{
	assert(transitionInfo != nullptr);

	return *transitionInfo;
}
