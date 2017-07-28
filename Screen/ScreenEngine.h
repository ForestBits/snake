#ifndef SCREENENGINE_H
#define SCREENENGINE_H

#include <SFML/Graphics.hpp>
#include "IScreen.h"
#include "ScreenStuff.h"
#include "ScreenChange.h"
#include "TransitionInfo.h"


class ScreenEngine
{
	friend class ScreenChange;

	//screenchange calls this with dynamically allocated screen
	void changeScreen(IScreen * screen);

	IScreen * currentScreen;
	IScreen * nextScreen;

	ScreenChange screenChange;

	ScreenStuff screenStuff;

	TransitionInfo transitionInfo;

	sf::Clock clock;

public:
	ScreenEngine(sf::RenderWindow & window, SoundPlayer & soundPlayer);

	ScreenChange & getScreenChange();

	const TransitionInfo & getTransitionInfo();

	void update();
	void draw();
};


#endif
