#include <cassert>
#include "ScreenList.h"

OptionsScreen::OptionsScreen(ScreenConstruct stuff) : soundVolumeSlider(stuff.resource), musicVolumeSlider(stuff.resource), globalVolumeSlider(stuff.resource), fullScreenCheckbox(stuff.resource), backButton(stuff.resource)
{
	backButton.setText("Menu");
	backButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, (stuff.window.getSize().y/5)*4), true);
	backButton.setOnClick([stuff] {if (!(stuff.transition.transitioningIn || stuff.transition.transitioningOut)) stuff.screenChange.setScreen<MainScreen>(stuff);});

	soundVolumeSlider.setPercent(stuff.soundPlayer.getVolume());
	soundVolumeSlider.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/5));
	soundVolumeSlider.setText("Sound");
	soundVolumeSlider.setOnMove([stuff] (float percent) {stuff.soundPlayer.setVolume(percent);});

	musicVolumeSlider.setPercent(stuff.musicPlayer.getVolume());
	musicVolumeSlider.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/3.3));
	musicVolumeSlider.setText("Music");
	musicVolumeSlider.setOnMove([stuff] (float percent) {stuff.musicPlayer.setVolume(percent);});

	assert(stuff.soundPlayer.getGlobalVolume() == stuff.musicPlayer.getGlobalVolume());

	globalVolumeSlider.setPercent(stuff.soundPlayer.getGlobalVolume());
	globalVolumeSlider.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/2.4));
	globalVolumeSlider.setText("Global");
	globalVolumeSlider.setOnMove([stuff] (float percent) {stuff.soundPlayer.setGlobalVolume(percent); stuff.musicPlayer.setGlobalVolume(percent);});

	fullScreenCheckbox.setChecked(stuff.window.getSize().x == sf::VideoMode::getFullscreenModes()[0].width && stuff.window.getSize().y == sf::VideoMode::getFullscreenModes()[0].height);
	fullScreenCheckbox.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/1.9));
	fullScreenCheckbox.setText("Fullscreen");
	fullScreenCheckbox.setOnToggle([this, stuff] (bool checked) 
	{
		if (checked) 
			stuff.window.create(sf::VideoMode(stuff.window.getSize().x, stuff.window.getSize().y), "Snake", sf::Style::Fullscreen);
		else
			stuff.window.create(sf::VideoMode(700, 500), "Snake");

		backButton.setPosition(sf::Vector2i(stuff.window.getSize().x/2, (stuff.window.getSize().y/5)*4), true);
		soundVolumeSlider.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/5));
		musicVolumeSlider.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/3.3));
		globalVolumeSlider.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/2.4));
		fullScreenCheckbox.setPosition(sf::Vector2i(stuff.window.getSize().x/2, stuff.window.getSize().y/1.9));
	});
}

void OptionsScreen::update(const ScreenStuff & stuff)
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

			backButton.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, (stuff.getWindow().getSize().y/5)*4), true);
			soundVolumeSlider.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/5));
			musicVolumeSlider.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/3.3));
			globalVolumeSlider.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/2.4));
			fullScreenCheckbox.setPosition(sf::Vector2i(stuff.getWindow().getSize().x/2, stuff.getWindow().getSize().y/1.9));
		}
	}

	backButton.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
	soundVolumeSlider.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
	musicVolumeSlider.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
	globalVolumeSlider.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());
	fullScreenCheckbox.update(sf::Mouse::getPosition(stuff.getWindow()), events, stuff.getSoundPlayer());

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

void OptionsScreen::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::White);

	target.draw(backButton);
	target.draw(soundVolumeSlider);
	target.draw(musicVolumeSlider);
	target.draw(globalVolumeSlider);
	target.draw(fullScreenCheckbox);

	transitionShape.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));
	
	target.draw(transitionShape);
}

float OptionsScreen::getTransitionInTime()
{
	return 1;
}

float OptionsScreen::getTransitionOutTime()
{
	return 1;
}
