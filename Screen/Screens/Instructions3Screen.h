#ifndef INSTRUCTIONS3SCREEN_H
#define INSTRUCTIONS3SCREEN_H

#include "ScreenHeaders.h"
#include "../../Input/Button.h"
#include "../../Game/Level.h"

class Instructions3Screen : public IScreen
{
	bool dead;

	sf::Text lessonText;

	Button backButton;
	Button leftButton;

	Level level;

	Level tempLevel;

	sf::Clock clock;

	sf::RectangleShape transitionShape;

public:
	Instructions3Screen(ScreenConstruct stuff);

	void update(const ScreenStuff & stuff);

	void draw(sf::RenderTarget & target);

	float getTransitionInTime();
	float getTransitionOutTime();
};


#endif
