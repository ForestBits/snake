#include "../../EventQueue.h"
#include "ScreenList.h"
#include <iostream>

MultiplayerGameScreen::MultiplayerGameScreen(ScreenConstruct stuff, bool twoPlayer, int computerCount, const SolidMap & map) : paused(false), construct(stuff), twoPlayer(twoPlayer), computerCount(computerCount)
{
	stuff.musicPlayer.stop(Musics::MENU_MUSIC);
	stuff.musicPlayer.play(Musics::GAME_MUSIC);

	pausedText.setCharacterSize(25);
	pausedText.setFont(stuff.resource.getFont());
	pausedText.setColor(sf::Color::Black);
	pausedText.setString("Paused");
	pausedText.setOrigin(pausedText.getLocalBounds().width/2, pausedText.getLocalBounds().height/2);
	pausedText.setPosition(stuff.window.getSize().x/2, stuff.window.getSize().y/20);

	//level is 60 x 32

	snakeCount = 1 + (twoPlayer ? computerCount + 1: computerCount);

	level.setMap(map);

	level.setOnEat([stuff] (const Snake & snake) {stuff.soundPlayer.play(Sounds::FOOD_SOUND);});
	level.setOnDeath([this, stuff] (const Snake & snake) 
	{
		stuff.musicPlayer.stop(Musics::GAME_MUSIC);
		stuff.musicPlayer.play(Musics::MENU_MUSIC);

		stuff.soundPlayer.play(Sounds::DEATH_SOUND);

		--snakeCount;
	});

	std::deque<sf::Vector2i> redBody, blueBody, greenBody, purpleBody;

	redBody.push_back(sf::Vector2i(5, 1));
	redBody.push_back(sf::Vector2i(4, 1));
	redBody.push_back(sf::Vector2i(3, 1));
	redBody.push_back(sf::Vector2i(2, 1));
	redBody.push_back(sf::Vector2i(1, 1));

	blueBody.push_back(sf::Vector2i(map.getSize().x - 6, map.getSize().y - 2));
	blueBody.push_back(sf::Vector2i(map.getSize().x - 5, map.getSize().y - 2));
	blueBody.push_back(sf::Vector2i(map.getSize().x - 4, map.getSize().y - 2));
	blueBody.push_back(sf::Vector2i(map.getSize().x - 3, map.getSize().y - 2));
	blueBody.push_back(sf::Vector2i(map.getSize().x - 2, map.getSize().y - 2));

	greenBody.push_back(sf::Vector2i(1, map.getSize().y - 6));
	greenBody.push_back(sf::Vector2i(1, map.getSize().y - 5));
	greenBody.push_back(sf::Vector2i(1, map.getSize().y - 4));
	greenBody.push_back(sf::Vector2i(1, map.getSize().y - 3));
	greenBody.push_back(sf::Vector2i(1, map.getSize().y - 2));

	purpleBody.push_back(sf::Vector2i(map.getSize().x - 2, 5));
	purpleBody.push_back(sf::Vector2i(map.getSize().x - 2, 4));
	purpleBody.push_back(sf::Vector2i(map.getSize().x - 2, 3));
	purpleBody.push_back(sf::Vector2i(map.getSize().x - 2, 2));
	purpleBody.push_back(sf::Vector2i(map.getSize().x - 2, 1));


	level.addSnake(Snake(sf::Color::Red, redBody, Direction::RIGHT, SnakeController::PLAYER_1));
	level.addSnake(Snake(sf::Color::Blue, blueBody, Direction::LEFT, twoPlayer ? SnakeController::PLAYER_2 : SnakeController::COMPUTER));

	if (computerCount > (twoPlayer ? 0 : 1))
		level.addSnake(Snake(sf::Color::Green, greenBody, Direction::DOWN, SnakeController::COMPUTER));

	if (computerCount > (twoPlayer ? 1 : 2))
		level.addSnake(Snake(sf::Color(175, 0, 191), purpleBody, Direction::UP, SnakeController::COMPUTER));
}

void MultiplayerGameScreen::update(const ScreenStuff & stuff)
{
	EventQueue events(stuff.getWindow());

	for (sf::Event evt : events)
	{
		if (evt.type == sf::Event::KeyPressed)
			if (evt.key.code == sf::Keyboard::P || evt.key.code == sf::Keyboard::Space)
			{
				stuff.getSoundPlayer().play(Sounds::PAUSE_SOUND);

				paused = !paused;
			}

		if (evt.type == sf::Event::Closed)
			stuff.getScreenChange().quit();

		if (evt.type == sf::Event::Resized)
		{
			stuff.getWindow().setSize(sf::Vector2u(evt.size.width, evt.size.height));

			sf::View view;

			view.setSize(stuff.getWindow().getSize().x, stuff.getWindow().getSize().y);
			view.setCenter(stuff.getWindow().getSize().x/2.f, stuff.getWindow().getSize().y/2.f);

			stuff.getWindow().setView(view);

			pausedText.setPosition(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/20);
		}
	}

	if (!(stuff.getTransitionInfo().transitioningIn || stuff.getTransitionInfo().transitioningOut))
	{
		level.inputCheck();

		if (clock.getElapsedTime().asSeconds() > 1.0/7 && startClock.getElapsedTime().asSeconds() > 2 && !paused)
		{
			clock.restart();

			level.update();

			if (snakeCount == 1)
			{
				stuff.getScreenChange().setScreen<MultiplayerWinScreen>(construct, twoPlayer, computerCount, level.getMap(), level.getSnake(0).getColor());
			}
			else if (snakeCount == 0)
			{
				//black signifies tie
				stuff.getScreenChange().setScreen<MultiplayerWinScreen>(construct, twoPlayer, computerCount, level.getMap(), sf::Color::Black);
			}
		}
	}

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

void MultiplayerGameScreen::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::White);

	level.draw(target, sf::FloatRect(0.05, 0.05, 0.9, 0.9));

	if (paused)
	{
		static sf::RectangleShape overlay;
		
		overlay.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));

		overlay.setFillColor(sf::Color(0, 0, 0, 80));

		target.draw(overlay);

		target.draw(pausedText);
	}

	transitionShape.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));

	target.draw(transitionShape);
}

float MultiplayerGameScreen::getTransitionInTime() {return 1;}
float MultiplayerGameScreen::getTransitionOutTime() {return 1;}