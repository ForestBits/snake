//where gamemode is selected (e.g. singleplayer, multiplayer)

#ifndef GAMEMODESELECTIONSCREEN_H
#define GAMEMODESELECTIONSCREEN_H

#include "../../Resource.h"
#include "ScreenHeaders.h"
#include "../../Input/Button.h"

class GamemodeSelectionScreen : public IScreen
{
	Resource & resource;

	sf::Text titleText;

	Button singleplayerButton;
	Button multiplayerButton;
	Button backButton;

	sf::RectangleShape transitionShape;

public:
	GamemodeSelectionScreen(ScreenConstruct stuff);

	void update(const ScreenStuff & stuff);

	void draw(sf::RenderTarget & target);

	float getTransitionInTime();
	float getTransitionOutTime();
};

#endif
