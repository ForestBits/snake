//main menu screen

#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <deque>
#include "ScreenHeaders.h"
#include "../../Particle/ParticleCollection.h"
#include "../../Resource.h"
#include "../../Input/Button.h"
#include "../../Input/Checkbox.h"
#include "../../Game/Level.h"

class MainScreen : public IScreen
{
	bool dead;

	std::deque<sf::Vector2i> body;

	Button playButton;
	Button highscoreButton;
	Button optionsButton;
	Button instructionsButton;
	Button creditsButton;
	Button quitButton;

	Level level;
	Level tempLevel;

	sf::Clock clock;

	sf::RectangleShape overlay;
	sf::RectangleShape transitionShape;

public:
	MainScreen(ScreenConstruct stuff);

	void update(const ScreenStuff & stuff);
	void draw(sf::RenderTarget & target);

	float getTransitionInTime();
	float getTransitionOutTime();
};

#endif
