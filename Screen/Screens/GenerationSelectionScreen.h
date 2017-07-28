//selecting type of generation for multiplayer

#include "ScreenHeaders.h"
#include "../../Input/Button.h"
#include "../../Game/Level.h"

class GenerationSelectionScreen : public IScreen
{
	//if another human player
	bool twoPlayer;

	int computerCount;

	Level top;
	Level middle;
	Level bottom;

	Button topButton;
	Button middleButton;
	Button bottomButton;
	Button backButton;

	sf::RectangleShape transitionShape;

public:
	GenerationSelectionScreen(ScreenConstruct stuff, bool twoPlayer, int computerCount);

	void update(const ScreenStuff & stuff);

	void draw(sf::RenderTarget & target);

	float getTransitionInTime();
	float getTransitionOutTime();
};