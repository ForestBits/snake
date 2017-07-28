//where players input highscores for singleplayer

#ifndef SINGLEPLAYERHIGHSCOREENTRYSCREEN_H
#define SINGLEPLAYERHIGHSCOREENTRYSCREEN_H

#include "../../Resource.h"
#include "../../Input/Button.h"
#include "../../Input/Textbox.h"
#include "ScreenHeaders.h"


class SingleplayerHighscoreEntryScreen : public IScreen
{
	int score;

	Button enterButton;

	Textbox playerNameTextbox;

	sf::Text titleText;
	sf::Text instructionsText;

	sf::RectangleShape transitionShape;

public:
	SingleplayerHighscoreEntryScreen(ScreenConstruct stuff, int score);

	void update(const ScreenStuff & stuff);

	void draw(sf::RenderTarget & target);

	float getTransitionInTime();
	float getTransitionOutTime();
};


#endif
