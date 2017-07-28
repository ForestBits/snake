//screens are basically game states
//here are some examples:
//main menu
//instructions
//gameplay

//each screen manages itself (updating, drawing)


#ifndef ISCREEN_H
#define ISCREEN_H

#include <SFML/Graphics.hpp>
#include "ScreenStuff.h"

class IScreen
{
public:
	virtual void update(const ScreenStuff & screenStuff) = 0;
	virtual void draw(sf::RenderTarget & target) = 0;

	virtual float getTransitionInTime() = 0;
	virtual float getTransitionOutTime() = 0;

	virtual ~IScreen() {}
};


#endif
