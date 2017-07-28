#include "../Resource.h"
#include "Button.h"

Button::Button(Resource & resource) : Button(resource, "", sf::Vector2i(0, 0), false)
{
	
}

Button::Button(Resource & resource, std::string string, sf::Vector2i position, bool centered) : text(string, resource.getFont(), 25), centered(centered)
{
	text.setColor(sf::Color::Black);

	setPosition(position, centered);
}

void Button::setText(std::string string)
{
	text.setString(string);

	//we recalculate this because centering changes based on the text
	setPosition(position, centered);
}

void Button::setPosition(sf::Vector2i position, bool centered)
{
	this->position = position;
	this->centered = centered;

	if (centered)
		text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
	else //it may have been set centered before, so clear the origin
		text.setOrigin(0, 0);

	text.setPosition(position.x, position.y);
}

void Button::setOnClick(std::function<void()> function)
{
	this->function = function;
}

void Button::update(sf::Vector2i mousePosition, EventQueue events, SoundPlayer & soundPlayer)
{
	bool mouseOver = text.getGlobalBounds().contains(sf::Vector2f(mousePosition.x, mousePosition.y));

	for (auto evt : events)
		if (evt.type == sf::Event::MouseButtonPressed)
			if (mouseOver)
			{
				soundPlayer.play(Sounds::CLICK_SOUND);

				if (function)
					function();
			}

	if (mouseOver)
		text.setStyle(sf::Text::Underlined);
	else
		text.setStyle(sf::Text::Regular);
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(text);
}