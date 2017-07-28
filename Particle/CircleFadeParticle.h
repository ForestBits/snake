//an expanding circle, that starts black, and fades

#ifndef CIRCLEFADEPARTICLE_H
#define CIRCLEFADEPARTICLE_H
#include <iostream>

#include <SFML/Graphics.hpp>

class CircleFadeParticle : public sf::Drawable
{
	inline void draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		sf::CircleShape circle;

		circle.setPointCount(100);
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineThickness(5);
		circle.setOutlineColor(sf::Color(0, 0, 0, (1 - (clock.getElapsedTime().asSeconds()/lifeSpan))*255));
		circle.setRadius(radius);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(position);

		target.draw(circle);
	}

public:
	inline CircleFadeParticle(sf::Vector2f position, float radius, float lifeSpan) : position(position), radius(radius), lifeSpan(lifeSpan) {}

	float radius;

	float lifeSpan;

	sf::Clock clock;

	sf::Vector2f position;

	inline bool operator==(const CircleFadeParticle & particle)
	{
		return (this->lifeSpan == particle.lifeSpan && this->position == particle.position && this->radius == particle.radius);
	}
};

#endif

