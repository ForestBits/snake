#include <deque>
#include "ScreenList.h"
#include "../../Generation/Generators.h"

Instructions1Screen::Instructions1Screen(ScreenConstruct stuff) : paused(false), leftDead(false), rightDead(false), rightButton(stuff.resource), backButton(stuff.resource)
{
	pauseShape.setFillColor(sf::Color(0, 0, 0, 50));

	std::deque<sf::Vector2i> body;

	for (int i = 9; i >= 0; --i)
		body.emplace_back(i + 1, 1);

	leftLevel.setMap(SolidMap(30, 16));
	rightLevel.setMap(SolidMap(30, 16));

	leftLevel.addSnake(Snake(sf::Color::Blue, body, Direction::RIGHT, SnakeController::PLAYER_2));
	rightLevel.addSnake(Snake(sf::Color::Red, body, Direction::RIGHT, SnakeController::PLAYER_1));

	leftLevel.setHasFood(false);
	rightLevel.setHasFood(false);

	leftLevel.setOnDeath([this] (const Snake & snake) {leftDead = true;});
	rightLevel.setOnDeath([this] (const Snake & snake) {rightDead = true;});

	tempLeftLevel = leftLevel;
	tempRightLevel = rightLevel;

	lessonText.setString("Move with ADWS or arrow keys");
	lessonText.setFont(stuff.resource.getFont());
	lessonText.setCharacterSize(10);
	lessonText.setColor(sf::Color::Black);
	lessonText.setOrigin(lessonText.getLocalBounds().width/2, lessonText.getLocalBounds().height/2);
	lessonText.setPosition(stuff.window.getSize().x/2, stuff.window.getSize().y/6);

	lessonText2.setString("Press P or Spacebar to pause");
	lessonText2.setFont(stuff.resource.getFont());
	lessonText2.setCharacterSize(10);
	lessonText2.setColor(sf::Color::Black);
	lessonText2.setOrigin(lessonText2.getLocalBounds().width/2, lessonText2.getLocalBounds().height/2);
	lessonText2.setPosition(stuff.window.getSize().x/2, stuff.window.getSize().y/5);

	rightButton.setText("Next");
	rightButton.setPosition(sf::Vector2i((stuff.window.getSize().x/20)*19, stuff.window.getSize().y/2), true);
	rightButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<Instructions2Screen>(stuff);});

	backButton.setText("Menu");
	backButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<MainScreen>(stuff);});
	backButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, (stuff.window.getSize().y/5.f)*4), true);
}

void Instructions1Screen::update(const ScreenStuff & stuff)
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

			lessonText.setPosition(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/6);
			lessonText2.setPosition(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/5);
			rightButton.setPosition(sf::Vector2i((stuff.getWindow().getSize().x/20)*19, stuff.getWindow().getSize().y/2), true);
			backButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, (stuff.getWindow().getSize().y/5.f)*4), true);
		}
	}

	tempLeftLevel.inputCheck();
	tempRightLevel.inputCheck();

	if (clock.getElapsedTime().asSeconds() > 0.3 && !paused)
	{
		clock.restart();

		tempLeftLevel.update();
		tempRightLevel.update();

		if (leftDead)
		{
			tempLeftLevel = leftLevel;

			leftDead = false;
		}

		if (rightDead)
		{
			tempRightLevel = rightLevel;

			rightDead = false;
		}
	}

	rightButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
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

void Instructions1Screen::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::White);

	tempLeftLevel.draw(target, sf::FloatRect(0.15, 0.2, 0.3, 0.7));
	tempRightLevel.draw(target, sf::FloatRect(0.55, 0.2, 0.3, 0.7));

	target.draw(lessonText);
	target.draw(lessonText2);

	target.draw(rightButton);
	target.draw(backButton);

	if (paused)
	{
		pauseShape.setSize(sf::Vector2f(0.7*target.getSize().x + 10, 0.23*target.getSize().y + 10));
		pauseShape.setPosition(0.148*target.getSize().x - 5, 0.435*target.getSize().y - 5);

		target.draw(pauseShape);
	}

	transitionShape.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));

	target.draw(transitionShape);
}

float Instructions1Screen::getTransitionInTime() {return 1;}
float Instructions1Screen::getTransitionOutTime() {return 1;}