#include <algorithm>
#include "../../EventQueue.h"
#include "../../Utility/StringNumberConvert.h"
#include "../../File/SaveOperations.h"
#include "ScreenList.h"

SingleplayerScoreScreen::SingleplayerScoreScreen(ScreenConstruct stuff, int score) : score(score), playButton(stuff.resource), menuButton(stuff.resource)
{
	scoreText.setCharacterSize(20);
	scoreText.setFont(stuff.resource.getFont());
	scoreText.setColor(sf::Color::Black);
	scoreText.setString("Your score: " + toString<int>(score));
	scoreText.setOrigin(scoreText.getLocalBounds().width/2, scoreText.getLocalBounds().height/2);
	scoreText.setPosition(stuff.window.getSize().x/2, stuff.window.getSize().y/5);

	playButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<GameScreen>(stuff);});
	playButton.setText("Play Again");
	playButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/2.8), true);

	menuButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<MainScreen>(stuff);});
	menuButton.setText("Menu");
	menuButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/2), true);
}

void SingleplayerScoreScreen::update(const ScreenStuff & stuff)
{
	EventQueue events(stuff.getWindow());

	for (sf::Event event : events)
	{
		if (event.type == sf::Event::Closed)
			stuff.getScreenChange().quit();

		if (event.type == sf::Event::Resized)
		{
			stuff.getWindow().setSize(sf::Vector2u(event.size.width, event.size.height));

			sf::View view;

			view.setSize(stuff.getWindow().getSize().x, stuff.getWindow().getSize().y);
			view.setCenter(stuff.getWindow().getSize().x/2.f, stuff.getWindow().getSize().y/2.f);

			stuff.getWindow().setView(view);

			scoreText.setPosition(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/5);
			playButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/2.8), true);
			menuButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/2), true);
		}
	}

	playButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
	menuButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());

	if (stuff.getTransitionInfo().transitioningIn)
	{
		transitionShape.setFillColor(sf::Color(255, 255, 255, (1 - stuff.getTransitionInfo().transitionPercent)*255));
	}
	else if (stuff.getTransitionInfo().transitioningOut)
	{
		transitionShape.setFillColor(sf::Color(255, 255, 255, stuff.getTransitionInfo().transitionPercent*255));
	}
	else
		transitionShape.setFillColor(sf::Color::Transparent);
}

void SingleplayerScoreScreen::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::White);

	target.draw(scoreText);
	
	target.draw(playButton);
	target.draw(menuButton);

	transitionShape.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));

	target.draw(transitionShape);
}

float SingleplayerScoreScreen::getTransitionInTime() 
{
	return 1;
}

float SingleplayerScoreScreen::getTransitionOutTime()
{
	return 1;
}