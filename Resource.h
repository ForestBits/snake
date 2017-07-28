//holds game resources such as fonts, images, audio

#ifndef RESOURCE_H
#define RESOURCE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Resource
{
private:
	sf::Font font;

	sf::SoundBuffer clickSoundBuffer;
	sf::SoundBuffer foodSoundBuffer;
	sf::SoundBuffer deathSoundBuffer;
	sf::SoundBuffer pauseSoundBuffer;

	sf::Image icon;
	sf::Image sfmlLogo;

public:
	//loads resources- throws Exception on failure
	Resource();

	const sf::Font & getFont();
	const sf::SoundBuffer & getClickSoundBuffer();
	const sf::SoundBuffer & getFoodSoundBuffer();
	const sf::SoundBuffer & getDeathSoundBuffer();
	const sf::SoundBuffer & getPauseSoundBuffer();
	const sf::Image & getIcon();
	const sf::Image & getSfmlLogo();
};

#endif
