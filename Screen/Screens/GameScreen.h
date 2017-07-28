#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "ScreenHeaders.h"
#include "../../Game/Level.h"
#include "../../Resource.h"
#include <string>

class GameScreen : public IScreen
{
	bool paused;

	Level level;

	sf::Text scoreText;
	sf::Text pausedText;

	sf::Clock clock;
	sf::Clock waitClock;

	sf::RectangleShape transitionShape;

public:
	GameScreen(ScreenConstruct stuff);

	void update(const ScreenStuff & stuff);

	void draw(sf::RenderTarget & target);

	float getTransitionInTime();
	float getTransitionOutTime();
};


#endif
