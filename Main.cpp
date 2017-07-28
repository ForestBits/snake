#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include <thread>
#include <fstream>
#include "Screen/ScreenEngine.h"
#include "Screen/Screens/MainScreen.h"
#include "Screen/Screens/ScreenConstruct.h"
#include "Generation/Generators.h"
#include "Resource.h"
#include "Exception.h"

int main()
{
	remove("error.txt");

	sf::RenderWindow window(sf::VideoMode(700, 500), "Snake");

	window.setKeyRepeatEnabled(false);

	sf::Clock clock;

	try
	{
		Resource resource;

		window.setIcon(resource.getIcon().getSize().x, resource.getIcon().getSize().y, resource.getIcon().getPixelsPtr());

		SoundPlayer soundPlayer(resource, 0.5);

		MusicPlayer musicPlayer(0.5);

		musicPlayer.setLoop(Musics::MENU_MUSIC, true);
		musicPlayer.setLoop(Musics::GAME_MUSIC, true);

		sf::Clock clock;

		ScreenEngine engine(window, soundPlayer);

		ScreenConstruct screenConstruct = {soundPlayer, musicPlayer, resource, engine.getScreenChange(), window, engine.getTransitionInfo()};

		engine.getScreenChange().setScreen<MainScreen>(screenConstruct);

		while (true)
		{
			if (clock.getElapsedTime().asSeconds() > 0.03)
			{
				clock.restart();
				
				engine.update();
				engine.draw();
				window.display();
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	catch (std::exception ex)
	{
		std::fstream file("error.txt", std::ios::out);

		file << "Error: " << ex.what();
	}

	catch (...)
	{
		std::fstream file("error.txt", std::ios::out);

		file << "An unknown error occured";
	}
}