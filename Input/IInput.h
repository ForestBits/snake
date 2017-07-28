//all input elements should implement this 

#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>
#include "../Screen/ScreenStuff.h"
#include "../EventQueue.h"


class IInput : public sf::Drawable
{
public:
	virtual void update(sf::Vector2i mousePosition, EventQueue events, SoundPlayer & soundPlayer) = 0;
};

#endif
