#ifndef INSTRUCTIONS1SCREEN_H
#define INSTRUCTIONS1SCREEN_H

#include "ScreenHeaders.h"
#include "../../Input/Button.h"
#include "../../Game/Level.h"

class Instructions1Screen : public IScreen
{
	bool leftDead, rightDead, paused;

	sf::Text lessonText;
	sf::Text lessonText2;

	Button backButton;
	Button rightButton;

	Level leftLevel;
	Level rightLevel;

	Level tempLeftLevel;
	Level tempRightLevel;

	sf::Clock clock;

	sf::RectangleShape pauseShape;
	sf::RectangleShape transitionShape;

public:
	Instructions1Screen(ScreenConstruct stuff);

	void update(const ScreenStuff & stuff);

	void draw(sf::RenderTarget & target);

	float getTransitionInTime();
	float getTransitionOutTime();
};


#endif
