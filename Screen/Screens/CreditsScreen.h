#ifndef CREDITSSCREEN_H
#define CREDITSSCREEN_H

#include "ScreenHeaders.h"
#include "ScreenConstruct.h"
#include "../../Input/Button.h"

class CreditsScreen : public IScreen
{
	sf::Text music1Text;
	sf::Text music2Text;

	sf::Texture logoTexture;
	
	sf::Sprite logo;

	Button backButton;

	sf::RectangleShape transitionShape;

public:
	CreditsScreen(ScreenConstruct stuff);

	void update(const ScreenStuff & stuff);

	void draw(sf::RenderTarget & target);

	float getTransitionInTime();
	float getTransitionOutTime();
};

#endif
