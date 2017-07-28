//states who wins, play again or menu options

#ifndef MULTIPLAYERWINSCREEN_H
#define MULTIPLAYERWINSCREEN_H

#include "../../Input/Button.h"
#include "ScreenHeaders.h"

class SolidMap;

class MultiplayerWinScreen : public IScreen
{
	sf::Text winText;
	sf::Text colorText;

	Button againButton;
	Button backButton;

	sf::RectangleShape transitionShape;

public:
	MultiplayerWinScreen(ScreenConstruct stuff, bool twoPlayer, int computerCount, const SolidMap & map, sf::Color winner);

	void update(const ScreenStuff & stuff);

	void draw(sf::RenderTarget & target);

	float getTransitionInTime();
	float getTransitionOutTime();
};



#endif
