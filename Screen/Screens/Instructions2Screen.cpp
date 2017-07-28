#include <deque>
#include "ScreenList.h"
#include "../../Generation/Generators.h"

Instructions2Screen::Instructions2Screen(ScreenConstruct stuff) : dead(false), leftButton(stuff.resource), rightButton(stuff.resource), backButton(stuff.resource)
{
	std::deque<sf::Vector2i> body;

	for (int i = 9; i >= 0; --i)
		body.emplace_back(i + 1, 1);

	level.setMap(generateRandomInteriorBlocks(30, 16, 2, 0.05));
	
	level.addSnake(Snake(sf::Color::Red, body, Direction::RIGHT, SnakeController::PLAYER_1));

	level.setHasFood(false);

	level.setOnDeath([this] (const Snake & snake) {dead = true;});

	tempLevel = level;

	lessonText.setString("Don't run into walls or yourself");
	lessonText.setFont(stuff.resource.getFont());
	lessonText.setCharacterSize(10);
	lessonText.setColor(sf::Color::Black);
	lessonText.setOrigin(lessonText.getLocalBounds().width/2, lessonText.getLocalBounds().height/2);
	lessonText.setPosition(stuff.window.getSize().x/2, stuff.window.getSize().y/6);

	leftButton.setText("Back");
	leftButton.setPosition(sf::Vector2i(stuff.window.getSize().x/20, stuff.window.getSize().y/2), true);
	leftButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<Instructions1Screen>(stuff);});

	rightButton.setText("Next");
	rightButton.setPosition(sf::Vector2i((stuff.window.getSize().x/20)*19, stuff.window.getSize().y/2), true);
	rightButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<Instructions3Screen>(stuff);});

	backButton.setText("Menu");
	backButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<MainScreen>(stuff);});
	backButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, (stuff.window.getSize().y/5.f)*4), true);
}

void Instructions2Screen::update(const ScreenStuff & stuff)
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

			lessonText.setPosition(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/6);
			leftButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/20, stuff.getWindow().getSize().y/2), true);
			rightButton.setPosition(sf::Vector2i((stuff.getWindow().getSize().x/20)*19, stuff.getWindow().getSize().y/2), true);
			backButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, (stuff.getWindow().getSize().y/5.f)*4), true);
		}
	}

	tempLevel.inputCheck();

	if (clock.getElapsedTime().asSeconds() > 0.3)
	{
		clock.restart();

		tempLevel.update();

		if (dead)
		{
			tempLevel = level;

			dead = false;
		}
	}

	leftButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
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

void Instructions2Screen::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::White);

	tempLevel.draw(target, sf::FloatRect(0.2, 0.2, 0.6, 0.6));

	target.draw(lessonText);

	target.draw(leftButton);
	target.draw(rightButton);
	target.draw(backButton);

	transitionShape.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));

	target.draw(transitionShape);
}

float Instructions2Screen::getTransitionInTime() {return 1;}
float Instructions2Screen::getTransitionOutTime() {return 1;}