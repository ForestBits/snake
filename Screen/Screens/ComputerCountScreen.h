//choose how many computers there will be

#include "ScreenHeaders.h"
#include "../../Input/NumberSelect.h"
#include "../../Input/Button.h"

class ComputerCountScreen : public IScreen
{
	//if another human player
	bool twoPlayer;

	NumberSelect computerNumberSelect;

	Button nextButton;
	Button backButton;

	sf::RectangleShape transitionShape;

public:
	ComputerCountScreen(ScreenConstruct stuff, bool twoPlayer);

	void update(const ScreenStuff & stuff);

	void draw(sf::RenderTarget & target);

	float getTransitionInTime();
	float getTransitionOutTime();
};