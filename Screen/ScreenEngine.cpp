#include "ScreenEngine.h"
#include <cassert>

ScreenEngine::ScreenEngine(sf::RenderWindow & window, SoundPlayer & soundPlayer) : currentScreen(nullptr), nextScreen(nullptr), screenChange(this)
{
	screenStuff.setWindow(window);
	screenStuff.setSoundPlayer(soundPlayer);
	screenStuff.setTransitionInfo(transitionInfo);
	screenStuff.setScreenChange(screenChange);

	transitionInfo.transitioningIn = false;
	transitionInfo.transitioningOut = false;
	transitionInfo.transitionPercent = 0;
}

ScreenChange & ScreenEngine::getScreenChange() {return screenChange;}

const TransitionInfo & ScreenEngine::getTransitionInfo() {return transitionInfo;}

void ScreenEngine::update()
{
	assert(currentScreen != nullptr);

	if (transitionInfo.transitioningIn)
	{
		transitionInfo.transitionPercent = clock.getElapsedTime().asSeconds()/currentScreen->getTransitionInTime();

		if (transitionInfo.transitionPercent >= 1)
		{
			transitionInfo.transitioningIn = false;

			transitionInfo.transitionPercent = 0;
		}
	}
	else if (transitionInfo.transitioningOut)
	{
		transitionInfo.transitionPercent = clock.getElapsedTime().asSeconds()/currentScreen->getTransitionOutTime();

		if (transitionInfo.transitionPercent >= 1)
		{
			delete currentScreen;

			currentScreen = nextScreen;

			nextScreen = nullptr;

			transitionInfo.transitioningOut = false;

			transitionInfo.transitioningIn = true;

			transitionInfo.transitionPercent = 0;

			clock.restart();
		}
	}


	currentScreen->update(screenStuff);
}

void ScreenEngine::draw()
{
	assert(currentScreen != nullptr);

	currentScreen->draw(screenStuff.getWindow());
}

void ScreenEngine::changeScreen(IScreen * screen)
{
	if (screen == nullptr)
	{
		delete nextScreen;

		delete currentScreen;

		std::exit(0);
	}

	//not sure what would be done if this happened
	assert(!(transitionInfo.transitioningIn || transitionInfo.transitioningOut));

	//if this is the initial room being set
	if (currentScreen == nullptr)
	{
		transitionInfo.transitioningIn = true;
		
		currentScreen = screen;
	}
	else
	{
		//normal changing

		transitionInfo.transitioningOut = true;

		nextScreen = screen;
	}

	clock.restart();
}