//both with human and with computer occurs here

#ifndef MULTIPLAYERGAMESCREEN_H
#define MULTIPLAYERGAMESCREEN_H

#include "../../Game/Level.h"
#include "ScreenHeaders.h"

class MultiplayerGameScreen : public IScreen
{
	bool twoPlayer;
	bool paused;

	int computerCount;

	int snakeCount;

	ScreenConstruct construct;

	Level level;

	sf::Clock clock;
	sf::Clock startClock;

	sf::Text pausedText;

	sf::RectangleShape transitionShape;

public:
	MultiplayerGameScreen(ScreenConstruct stuff, bool twoPlayer, int computerCount, const SolidMap & map);

	void update(const ScreenStuff & stuff);

	void draw(sf::RenderTarget & target);

	float getTransitionInTime();
	float getTransitionOutTime();
};


#endif
