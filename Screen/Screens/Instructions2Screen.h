#ifndef INSTRUCTIONS2SCREEN_H
#define INSTRUCTIONS2SCREEN_H

#include "ScreenHeaders.h"
#include "../../Input/Button.h"
#include "../../Game/Level.h"

class Instructions2Screen : public IScreen
{
	bool dead;

	sf::Text lessonText;

	Button backButton;
	Button leftButton;
	Button rightButton;

	Level level;

	Level tempLevel;

	sf::Clock clock;

	sf::RectangleShape transitionShape;

public:
	Instructions2Screen(ScreenConstruct stuff);

	void update(const ScreenStuff & stuff);

	void draw(sf::RenderTarget & target);

	float getTransitionInTime();
	float getTransitionOutTime();
};


#endif
