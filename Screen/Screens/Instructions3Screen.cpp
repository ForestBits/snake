#include <deque>
#include "ScreenList.h"
#include "../../Generation/Generators.h"

Instructions3Screen::Instructions3Screen(ScreenConstruct stuff) : dead(false), leftButton(stuff.resource), backButton(stuff.resource)
{
	std::deque<sf::Vector2i> body;

	for (int i = 9; i >= 0; --i)
		body.emplace_back(i + 1, 1);

	level.setMap(generateWalled(30, 16));
	
	level.addSnake(Snake(sf::Color::Red, body, Direction::RIGHT, SnakeController::PLAYER_1));

	level.setOnDeath([this] (const Snake & snake) {dead = true;});

	tempLevel = level;

	lessonText.setString("Run into food to get bigger");
	lessonText.setFont(stuff.resource.getFont());
	lessonText.setCharacterSize(10);
	lessonText.setColor(sf::Color::Black);
	lessonText.setOrigin(lessonText.getLocalBounds().width/2, lessonText.getLocalBounds().height/2);
	lessonText.setPosition(stuff.window.getSize().x/2, stuff.window.getSize().y/6);

	leftButton.setText("Back");
	leftButton.setPosition(sf::Vector2i(stuff.window.getSize().x/20, stuff.window.getSize().y/2), true);
	leftButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<Instructions2Screen>(stuff);});

	backButton.setText("Menu");
	backButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<MainScreen>(stuff);});
	backButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, (stuff.window.getSize().y/5.f)*4), true);
}

void Instructions3Screen::update(const ScreenStuff & stuff)
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

void Instructions3Screen::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::White);

	tempLevel.draw(target, sf::FloatRect(0.2, 0.2, 0.6, 0.6));

	target.draw(lessonText);

	target.draw(leftButton);
	target.draw(backButton);

	transitionShape.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));

	target.draw(transitionShape);
}

float Instructions3Screen::getTransitionInTime() {return 1;}
float Instructions3Screen::getTransitionOutTime() {return 1;}