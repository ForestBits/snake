#include "../../EventQueue.h"
#include <fstream>
#include <deque>
#include "ScreenList.h"
#include "../../Utility/StringNumberConvert.h"
#include "../../Generation/Generators.h"
#include "../../File/SaveOperations.h"

GameScreen::GameScreen(ScreenConstruct stuff) : paused(false)
{
	stuff.musicPlayer.stop(Musics::MENU_MUSIC);
	stuff.musicPlayer.play(Musics::GAME_MUSIC);

	scoreText.setCharacterSize(20);
	scoreText.setFont(stuff.resource.getFont());
	scoreText.setColor(sf::Color::Black);
	scoreText.setPosition(stuff.window.getSize().x/70, stuff.window.getSize().y/50);

	pausedText.setCharacterSize(25);
	pausedText.setFont(stuff.resource.getFont());
	pausedText.setColor(sf::Color::Black);
	pausedText.setString("Paused");
	pausedText.setOrigin(pausedText.getLocalBounds().width/2, pausedText.getLocalBounds().height/2);
	pausedText.setPosition(stuff.window.getSize().x/2, stuff.window.getSize().y/6);

	level.setOnEat([this, stuff] (const Snake & snake) 
	{
		stuff.soundPlayer.play(Sounds::FOOD_SOUND);

		scoreText.setString(toString<int>(snake.getLength()));
	});

	level.setOnDeath([stuff] (const Snake & snake) 
	{
		stuff.musicPlayer.stop(Musics::GAME_MUSIC);
		stuff.musicPlayer.play(Musics::MENU_MUSIC);

		stuff.soundPlayer.play(Sounds::DEATH_SOUND);

		//you can enter a score if:
		//A), there are less than 10 scores
		//or B), your score is greater than score 10

		auto scores = getScores("scores.txt", 10);

		//highest first
		std::sort(scores.begin(), scores.end(), [] (const std::pair<std::string, int> & score1, const std::pair<std::string, int> & score2) {return score1.second > score2.second;});

		int lastScoreIndex = scores.size() >= 10 ? 9 : scores.size() - 1;

		if (lastScoreIndex < 9 || snake.getLength() > scores[lastScoreIndex].second)
			stuff.screenChange.setScreen<SingleplayerHighscoreEntryScreen>(stuff, snake.getLength());
		else
			stuff.screenChange.setScreen<SingleplayerScoreScreen>(stuff, snake.getLength());
	});

	std::deque<sf::Vector2i> snakeBody;

	snakeBody.push_back(sf::Vector2i(5, 1));
	snakeBody.push_back(sf::Vector2i(4, 1));
	snakeBody.push_back(sf::Vector2i(3, 1));
	snakeBody.push_back(sf::Vector2i(2, 1));
	snakeBody.push_back(sf::Vector2i(1, 1));

	level.setMap(generateWalled(30, 15));
	level.addSnake(Snake(sf::Color::Red, snakeBody, Direction::RIGHT, SnakeController::PLAYER_1));

	scoreText.setString("5");
}


void GameScreen::update(const ScreenStuff & stuff)
{
	level.inputCheck();

	if (!(stuff.getTransitionInfo().transitioningIn || stuff.getTransitionInfo().transitioningOut))
	{
		float period = (-std::log10(level.getSnake(0).getLength()))*0.1 + 0.3;

		if (period < 0.05)
			period = 0.05;

		if (clock.getElapsedTime().asSeconds() > period && waitClock.getElapsedTime().asSeconds() > 2 && !paused)
		{
			level.update();
		
			clock.restart();
		}
	}

	EventQueue events(stuff.getWindow());

	for (sf::Event evt : events)
	{
		if (evt.type == sf::Event::KeyPressed)
			if (evt.key.code == sf::Keyboard::P || evt.key.code == sf::Keyboard::Space && !(stuff.getTransitionInfo().transitioningIn || stuff.getTransitionInfo().transitioningOut))
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

			scoreText.setPosition(stuff.getWindow().getSize().x/70, stuff.getWindow().getSize().y/50);
			pausedText.setPosition(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/6);
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

void GameScreen::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::White);

	level.draw(target, sf::FloatRect(0.1, 0.1, 0.8, 0.8));

	target.draw(scoreText);

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

float GameScreen::getTransitionInTime() 
{
	return 1;
}

float GameScreen::getTransitionOutTime()
{
	return 1;
}