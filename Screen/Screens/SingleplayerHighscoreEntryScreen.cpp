#include "../../File/SaveOperations.h"
#include "../../Utility/StringNumberConvert.h"
#include "ScreenList.h"

SingleplayerHighscoreEntryScreen::SingleplayerHighscoreEntryScreen(ScreenConstruct stuff, int score) : enterButton(stuff.resource), playerNameTextbox(stuff.resource, 7)
{
	titleText.setCharacterSize(25);
	titleText.setColor(sf::Color::Black);
	titleText.setFont(stuff.resource.getFont());
	titleText.setString("You have gotten a highscore: " + toString(score));
	titleText.setOrigin(titleText.getLocalBounds().width/2, titleText.getLocalBounds().height/2);
	titleText.setPosition(stuff.window.getSize().x/2, stuff.window.getSize().y/8.5);

	instructionsText.setCharacterSize(25);
	instructionsText.setColor(sf::Color::Black);
	instructionsText.setFont(stuff.resource.getFont());
	instructionsText.setString("Please enter your name.");
	instructionsText.setOrigin(instructionsText.getLocalBounds().width/2, instructionsText.getLocalBounds().height/2);
	instructionsText.setPosition(stuff.window.getSize().x/2, stuff.window.getSize().y/5);

	playerNameTextbox.setLabel("Name");
	playerNameTextbox.setPosition(sf::Vector2i(stuff.window.getSize().x/2.2, stuff.window.getSize().y/2));


	enterButton.setOnClick([stuff, this, score]
	{
		if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut))
		{
			if (!playerNameTextbox.getContents().empty())
			{
				writeScore("scores.txt", std::make_pair(playerNameTextbox.getContents(), score));

				stuff.screenChange.setScreen<MainScreen>(stuff);
			}
		}
	});

	enterButton.setText("Enter");
	enterButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2.2, stuff.window.getSize().y/1.5), false);
}

void SingleplayerHighscoreEntryScreen::update(const ScreenStuff & stuff)
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

			titleText.setPosition(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/8.5);
			instructionsText.setPosition(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/5);
			playerNameTextbox.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2.2, stuff.getWindow().getSize().y/2));
			enterButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2.2, stuff.getWindow().getSize().y/1.5), false);
		}
	}

	playerNameTextbox.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
	enterButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());

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

void SingleplayerHighscoreEntryScreen::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::White);

	target.draw(titleText);
	target.draw(instructionsText);
	target.draw(playerNameTextbox);
	target.draw(enterButton);

	transitionShape.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));

	target.draw(transitionShape);
}

float SingleplayerHighscoreEntryScreen::getTransitionInTime()
{
	return 1;
}

float SingleplayerHighscoreEntryScreen::getTransitionOutTime()
{
	return 1;
}