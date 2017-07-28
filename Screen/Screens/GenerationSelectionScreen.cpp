#include "ScreenList.h"
#include "../../Generation/Generators.h"

GenerationSelectionScreen::GenerationSelectionScreen(ScreenConstruct stuff, bool twoPlayer, int computerCount) : topButton(stuff.resource), middleButton(stuff.resource), bottomButton(stuff.resource), backButton(stuff.resource)
{
	top.setMap(generateTunneled(60, 32, 2, 10));
	middle.setMap(generateRandomInteriorBlocks(60, 32, 2, 0.1));
	bottom.setMap(generateRandomScatteredBlocks(60, 32, 2, 0.007));

	top.setHasFood(false);
	middle.setHasFood(false);
	bottom.setHasFood(false);

	topButton.setText("Tunneled");
	topButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/35), true);
	topButton.setOnClick([this, stuff, twoPlayer, computerCount] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<MultiplayerGameScreen>(stuff, twoPlayer, computerCount, top.getMap());});

	middleButton.setText("Islands");
	middleButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/4.3), true);
	middleButton.setOnClick([this, stuff, twoPlayer, computerCount] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<MultiplayerGameScreen>(stuff, twoPlayer, computerCount, middle.getMap());});

	bottomButton.setText("Minefield");
	bottomButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/2.3), true);
	bottomButton.setOnClick([this, stuff, twoPlayer, computerCount] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<MultiplayerGameScreen>(stuff, twoPlayer, computerCount, bottom.getMap());});

	backButton.setText("Back");
	backButton.setOnClick([stuff, twoPlayer] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<ComputerCountScreen>(stuff, twoPlayer);});
	backButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, (stuff.window.getSize().y/5)*4), true);
}

void GenerationSelectionScreen::update(const ScreenStuff & stuff)
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

			topButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/35), true);
			middleButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/4.3), true);
			bottomButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/2.3), true);
			backButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, (stuff.getWindow().getSize().y/5)*4), true);
		}
	}

	topButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
	middleButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
	bottomButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
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

void GenerationSelectionScreen::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::White);

	top.draw(target, sf::FloatRect(0.1, 0.07, 0.8, 0.15));
	middle.draw(target, sf::FloatRect(0.1, 0.27, 0.8, 0.15));
	bottom.draw(target, sf::FloatRect(0.1, 0.47, 0.8, 0.15));

	target.draw(topButton);
	target.draw(middleButton);
	target.draw(bottomButton);
	target.draw(backButton);

	transitionShape.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));

	target.draw(transitionShape);
}

float GenerationSelectionScreen::getTransitionInTime()
{
	return 1;
}

float GenerationSelectionScreen::getTransitionOutTime()
{
	return 1;
}