//choose if playing with a second human player or not

#include "ScreenHeaders.h"
#include "../../Input/Button.h"


class MultiplayerTypeScreen : public IScreen
{
	Button humanButton;
	Button computerButton;
	Button backButton;

	sf::RectangleShape transitionShape;

public:
	MultiplayerTypeScreen(ScreenConstruct stuff);

	void update(const ScreenStuff & stuff);

	void draw(sf::RenderTarget & target);

	float getTransitionInTime();
	float getTransitionOutTime();
};