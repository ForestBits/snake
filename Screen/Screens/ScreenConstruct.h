//many screens make use of parameters in their constructors
//often used to set lambdas and similar
//screens that don't use things still need them
//to pass to the next screen, which didn't scale well
//so now it is this

#ifndef SCREENCONSTRUCT_H
#define SCREENCONSTRUCT_H

#include <SFML/Graphics.hpp>
#include "../../Audio/SoundPlayer.h"
#include "../ScreenChange.h"
#include "../../Resource.h"
#include "../TransitionInfo.h"

struct ScreenConstruct
{
	SoundPlayer & soundPlayer;

	MusicPlayer & musicPlayer;

	Resource & resource;

	ScreenChange & screenChange;

	sf::RenderWindow & window;

	const TransitionInfo & transition;
};

#endif
