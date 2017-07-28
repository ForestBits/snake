#include "ScreenList.h"

CreditsScreen::CreditsScreen(ScreenConstruct stuff) : backButton(stuff.resource)
{
	music1Text.setFont(stuff.resource.getFont());
	music1Text.setColor(sf::Color::Black);
	music1Text.setCharacterSize(20);
	music1Text.setString("\"Electrodoodle\" Kevin MacLeod (incompetech.com)");
	music1Text.setOrigin(music1Text.getLocalBounds().width/2, music1Text.getLocalBounds().height/2);
	music1Text.setPosition(stuff.window.getSize().x/2, stuff.window.getSize().y/4);

	music2Text.setFont(stuff.resource.getFont());
	music2Text.setColor(sf::Color::Black);
	music2Text.setCharacterSize(20);
	music2Text.setString("\"Pamgaea\" Kevin MacLeod (incompetech.com)");
	music2Text.setOrigin(music2Text.getLocalBounds().width/2, music2Text.getLocalBounds().height/2);
	music2Text.setPosition(stuff.window.getSize().x/2, stuff.window.getSize().y/3);

	logoTexture.loadFromImage(stuff.resource.getSfmlLogo());
	
	logo.setTexture(logoTexture);
	logo.setOrigin(logo.getLocalBounds().width/2, logo.getLocalBounds().height/2);
	logo.setPosition(stuff.window.getSize().x/2, stuff.window.getSize().y/1.7);

	backButton.setText("Menu");
	backButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<MainScreen>(stuff);});
	backButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, (stuff.window.getSize().y/5.f)*4), true);
}

void CreditsScreen::update(const ScreenStuff & stuff)
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


			music1Text.setPosition(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/4);
			music2Text.setPosition(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/3);
			logo.setPosition(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/1.7);
			backButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, (stuff.getWindow().getSize().y/5.f)*4), true);
		}
	}

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

void CreditsScreen::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::White);

	target.draw(music1Text);
	target.draw(music2Text);

	target.draw(logo);

	target.draw(backButton);

	transitionShape.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));

	target.draw(transitionShape);
}

float CreditsScreen::getTransitionInTime() {return 1;}
float CreditsScreen::getTransitionOutTime() {return 1;}