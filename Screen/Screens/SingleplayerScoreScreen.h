//showing score for singleplayer when you don't make the highscore list

#ifndef SINGLEPLAYERSCORESCREEN_H
#define SINGLEPLAYERSCORESCREEN_H

#include "../../Resource.h"
#include "../../Input/Button.h"
#include "ScreenHeaders.h"

class SingleplayerScoreScreen : public IScreen
{
	int score;

	sf::Text scoreText;

	Button playButton;
	Button menuButton;

	sf::RectangleShape transitionShape;

public:
	SingleplayerScoreScreen(ScreenConstruct stuff, int score);

	void update(const ScreenStuff & stuff);

	void draw(sf::RenderTarget & target);

	float getTransitionInTime();
	float getTransitionOutTime();
};

#endif

