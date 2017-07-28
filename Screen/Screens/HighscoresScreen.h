//displays singleplayer highscores (linked to main menu)

#ifndef HIGHSCORESSCREEN_H
#define HIGHSCORESSCREEN_H

#include <array>
#include "../../Input/Button.h"
#include "ScreenHeaders.h"
#include "../../Resource.h"

class HighscoresScreen : public IScreen
{
	std::array<std::string, 10> names;
	std::array<std::string, 10> numbers;

	sf::Text text;

	Button backButton;
	Button clearButton;

	sf::RectangleShape transitionShape;

public:
	HighscoresScreen(ScreenConstruct stuff);

	void update(const ScreenStuff & stuff);

	void draw(sf::RenderTarget & target);

	float getTransitionInTime();
	float getTransitionOutTime();

};

#endif
