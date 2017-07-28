#include "ScreenList.h"

MultiplayerWinScreen::MultiplayerWinScreen(ScreenConstruct stuff, bool twoPlayer, int computerCount, const SolidMap & map, sf::Color winner) : againButton(stuff.resource), backButton(stuff.resource)
{
	winText.setFont(stuff.resource.getFont());
	winText.setCharacterSize(20);
	winText.setColor(sf::Color::Black);
	winText.setString("Winner: ");
	winText.setPosition(stuff.window.getSize().x/2.5, stuff.window.getSize().y/5);

	colorText.setFont(stuff.resource.getFont());
	colorText.setCharacterSize(20);
	colorText.setPosition(stuff.window.getSize().x/1.95, stuff.window.getSize().y/5);
	colorText.setColor(winner);

	if (winner == sf::Color::Red)
		colorText.setString("Red");

	if (winner == sf::Color::Blue)
		colorText.setString("Blue");

	if (winner == sf::Color::Green)
		colorText.setString("Green");

	if (winner == sf::Color(175, 0, 191))
		colorText.setString("Purple");

	if (winner == sf::Color::Black)
		colorText.setString("Tie!");

	againButton.setOnClick([stuff, twoPlayer, computerCount, map] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<MultiplayerGameScreen>(stuff, twoPlayer, computerCount, map);});
	againButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/1.5), true);
	againButton.setText("Play again");

	backButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<MainScreen>(stuff);});
	backButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, (stuff.window.getSize().y/5)*4), true);
	backButton.setText("Menu");
}

void MultiplayerWinScreen::update(const ScreenStuff & stuff)
{
	EventQueue events(stuff.getWindow());

	for (sf::Event evt : events)
	{
		if (evt.type == sf::Event::Closed)
			stuff.getScreenChange().quit();

		if (evt.type == sf::Event::Resized)
		{
			stuff.getWindow().setSize(sf::Vector2u(evt.size.width, evt.size.height));

			sf::View view;

			view.setSize(stuff.getWindow().getSize().x, stuff.getWindow().getSize().y);
			view.setCenter(stuff.getWindow().getSize().x/2.f, stuff.getWindow().getSize().y/2.f);

			stuff.getWindow().setView(view);

			winText.setPosition(stuff.getWindow().getSize().x/2.5, stuff.getWindow().getSize().y/5);
			colorText.setPosition(stuff.getWindow().getSize().x/1.95, stuff.getWindow().getSize().y/5);

			againButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/1.5), true);
			backButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, (stuff.getWindow().getSize().y/5)*4), true);
		}
	}

	againButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
	backButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());

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

void MultiplayerWinScreen::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::White);

	target.draw(winText);
	target.draw(colorText);

	target.draw(againButton);
	target.draw(backButton);

	transitionShape.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));

	target.draw(transitionShape);
}

float MultiplayerWinScreen::getTransitionInTime() {return 1;}
float MultiplayerWinScreen::getTransitionOutTime() {return 1;}