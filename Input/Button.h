//a simple text button - allows action when it is clicked

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include "../Resource.h"
#include "../Audio/SoundPlayer.h"
#include "IInput.h"

class Button : public IInput
{
	sf::Text text;

	sf::Vector2i position;

	bool centered;

	std::function<void()> function;

public:
	Button(Resource & resource);
	Button(Resource & resource, std::string string, sf::Vector2i position, bool centered = false);

	void setText(std::string string);
	void setPosition(sf::Vector2i position, bool centered = false);
	void setOnClick(std::function<void()> function);

	void update(sf::Vector2i mousePosition, EventQueue events, SoundPlayer & soundPlayer);
	
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

#endif
