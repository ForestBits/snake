#include "ScreenList.h"

ComputerCountScreen::ComputerCountScreen(ScreenConstruct stuff, bool twoPlayer) : twoPlayer(twoPlayer), computerNumberSelect(stuff.resource), nextButton(stuff.resource), backButton(stuff.resource)
{
	std::vector<int> numbers;

	if (!twoPlayer)
	{
		numbers.push_back(1);
		numbers.push_back(2);
		numbers.push_back(3);
	}
	else
	{
		numbers.push_back(0);
		numbers.push_back(1);
		numbers.push_back(2);
	}
	
	computerNumberSelect.setNumbers(numbers, numbers[0]);
	computerNumberSelect.setText("Computer count");
	computerNumberSelect.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/2));

	nextButton.setText("Next");
	nextButton.setOnClick([stuff, twoPlayer, this] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<GenerationSelectionScreen>(stuff, twoPlayer, computerNumberSelect.getSelectedNumber());});
	nextButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, (stuff.window.getSize().y/5)*3.5), true);

	backButton.setText("Back");
	backButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<MultiplayerTypeScreen>(stuff);});
	backButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, (stuff.window.getSize().y/5)*4), true);
}

void ComputerCountScreen::update(const ScreenStuff & stuff)
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

			computerNumberSelect.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/2));

			nextButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, (stuff.getWindow().getSize().y/5)*3.5), true);
			backButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, (stuff.getWindow().getSize().y/5)*4), true);
		}
	}

	computerNumberSelect.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
	nextButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
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

void ComputerCountScreen::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::White);

	target.draw(computerNumberSelect);
	target.draw(nextButton);
	target.draw(backButton);

	transitionShape.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));

	target.draw(transitionShape);
}

float ComputerCountScreen::getTransitionInTime()
{
	return 1;
}

float ComputerCountScreen::getTransitionOutTime()
{
	return 1;
}