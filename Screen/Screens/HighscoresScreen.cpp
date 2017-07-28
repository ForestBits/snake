#include "../../File/SaveOperations.h"
#include "../../Utility/StringNumberConvert.h"
#include "ScreenList.h"

HighscoresScreen::HighscoresScreen(ScreenConstruct stuff) : backButton(stuff.resource), clearButton(stuff.resource), text("", stuff.resource.getFont(), 25)
{
	backButton.setText("Menu");
	backButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<MainScreen>(stuff);});
	backButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, (stuff.window.getSize().y/5.f)*4), true);

	clearButton.setText("Clear Scores");
	clearButton.setOnClick([this] 
	{
		clearScores("scores.txt");

		writeScore("scores.txt", std::make_pair("Garter", 10));
		writeScore("scores.txt", std::make_pair("Coral", 20));
		writeScore("scores.txt", std::make_pair("Copperhead", 30));
		writeScore("scores.txt", std::make_pair("Cottonmouth", 40));
		writeScore("scores.txt", std::make_pair("Viper", 50));
		writeScore("scores.txt", std::make_pair("Python", 75));
		writeScore("scores.txt", std::make_pair("Rattlesnake", 100));
		writeScore("scores.txt", std::make_pair("Cobra", 150));
		writeScore("scores.txt", std::make_pair("Anaconda", 200));
		writeScore("scores.txt", std::make_pair("Boa", 300));

		auto scores = getScores("scores.txt", 10);

		for (int i = 0; i < scores.size(); ++i)
		{
			names[i] = scores[i].first;
			numbers[i] = toString(scores[i].second);
		}
	});

	clearButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/12), true);

	text.setColor(sf::Color::Black);

	auto scores = getScores("scores.txt", 10);

	if (scores.size() < 10)
	{
		//default filler scores

		writeScore("scores.txt", std::make_pair("Garter", 10));
		writeScore("scores.txt", std::make_pair("Coral", 20));
		writeScore("scores.txt", std::make_pair("Copperhead", 30));
		writeScore("scores.txt", std::make_pair("Cottonmouth", 40));
		writeScore("scores.txt", std::make_pair("Viper", 50));
		writeScore("scores.txt", std::make_pair("Python", 75));
		writeScore("scores.txt", std::make_pair("Rattlesnake", 100));
		writeScore("scores.txt", std::make_pair("Cobra", 150));
		writeScore("scores.txt", std::make_pair("Anaconda", 200));
		writeScore("scores.txt", std::make_pair("Boa", 300));

		scores = getScores("scores.txt", 10);
	}

	for (int i = 0; i < scores.size(); ++i)
	{
		names[i] = scores[i].first;
		numbers[i] = toString(scores[i].second);
	}
}

void HighscoresScreen::update(const ScreenStuff & stuff)
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

			backButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, (stuff.getWindow().getSize().y/5.f)*4), true);
			clearButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/12), true);
		}
	}

	backButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
	clearButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());

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

void HighscoresScreen::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::White);

	for (int i = 0; i < names.size(); ++i)
	{
		text.setString(names[i]);

		text.setPosition(target.getSize().x/3.2, target.getSize().y/7 + i*(target.getSize().y/16.6));

		target.draw(text);

		text.setString(numbers[i]);

		text.setPosition((target.getSize().x/3.5)*2, target.getSize().y/7 + i*(target.getSize().y/16.6));

		target.draw(text);
	}

	target.draw(backButton);
	target.draw(clearButton);

	transitionShape.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));

	target.draw(transitionShape);
}

float HighscoresScreen::getTransitionInTime()
{
	return 1;
}

float HighscoresScreen::getTransitionOutTime()
{
	return 1;
}