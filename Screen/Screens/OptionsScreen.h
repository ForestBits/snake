//options room - fullscreen, volume settings

#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include "ScreenHeaders.h"
#include "../../Input/Slider.h"
#include "../../Input/Button.h"
#include "../../Input/Checkbox.h"
#include "../../Resource.h"

class OptionsScreen : public IScreen
{
	Slider soundVolumeSlider;
	Slider musicVolumeSlider;
	Slider globalVolumeSlider;

	Checkbox fullScreenCheckbox;

	Button backButton;

	sf::RectangleShape transitionShape;

public:
	OptionsScreen(ScreenConstruct stuff);

	void update(const ScreenStuff & stuff);

	void draw(sf::RenderTarget & target);

	float getTransitionInTime();
	float getTransitionOutTime();
};


#endif
