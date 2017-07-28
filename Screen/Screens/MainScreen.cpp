#include "../../EventQueue.h"
#include "ScreenList.h"
#include "../../Generation/WalledGenerator.h"

MainScreen::MainScreen(ScreenConstruct stuff) : dead(false), playButton(stuff.resource), highscoreButton(stuff.resource), optionsButton(stuff.resource), instructionsButton(stuff.resource), creditsButton(stuff.resource), quitButton(stuff.resource)
{
	level.setMap(generateWalled(60, 32));

	body.push_back(sf::Vector2i(5, 1));
	body.push_back(sf::Vector2i(4, 1));
	body.push_back(sf::Vector2i(3, 1));
	body.push_back(sf::Vector2i(2, 1));
	body.push_back(sf::Vector2i(1, 1));

	level.addSnake(Snake(sf::Color::Red, body, Direction::RIGHT, SnakeController::COMPUTER));
	
	level.setOnDeath([this] (const Snake & snake) {dead = true;});

	tempLevel = level;

	playButton.setText("Play");
	playButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<GamemodeSelectionScreen>(stuff);});
	playButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/5), true);

	highscoreButton.setText("Highscores");
	highscoreButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<HighscoresScreen>(stuff);});
	highscoreButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/3.5), true);

	optionsButton.setText("Options");
	optionsButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<OptionsScreen>(stuff);});
	optionsButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/2.6), true);

	instructionsButton.setText("Instructions");
	instructionsButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<Instructions1Screen>(stuff);});
	instructionsButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/2.1), true);

	creditsButton.setText("Credits");
	creditsButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<CreditsScreen>(stuff);});
	creditsButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/1.75), true);

	quitButton.setText("Quit");
	quitButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.quit();});
	quitButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/1.5), true);

	if (stuff.musicPlayer.getStatus(Musics::MENU_MUSIC) !=  sf::SoundSource::Playing)
		stuff.musicPlayer.play(Musics::MENU_MUSIC);
}

void MainScreen::update(const ScreenStuff & stuff)
{
	EventQueue events(stuff.getWindow());

	if (clock.getElapsedTime().asSeconds() > 0.2)
	{
		clock.restart();

		tempLevel.update();

		if (dead)
		{
			tempLevel = level;

			dead = false;
		}
	}

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

			playButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/5), true);
			highscoreButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/3.5), true);
			optionsButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/2.6), true);
			instructionsButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/2.1), true);
			creditsButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/1.75), true);
			quitButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/1.5), true);
		}
	}

	playButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
	highscoreButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
	optionsButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
	instructionsButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
	creditsButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
	quitButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());

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

void MainScreen::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::White);

	tempLevel.draw(target, sf::FloatRect(0.05, 0.05, 0.9, 0.9));

	overlay.setFillColor(sf::Color(255, 255, 255, 200));
	overlay.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));

	target.draw(overlay);

	target.draw(playButton);
	target.draw(highscoreButton);
	target.draw(optionsButton);
	target.draw(instructionsButton);
	target.draw(creditsButton);
	target.draw(quitButton);

	transitionShape.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));

	target.draw(transitionShape);
}

float MainScreen::getTransitionInTime() {return 1;}
float MainScreen::getTransitionOutTime() {return 1;}