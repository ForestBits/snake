//snakes manage their own bodies

#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include "Direction.h"
#include "MoveStatus.h"
#include "SnakeController.h"
#include "../SolidMap.h"

class Snake
{
	sf::Color color;

	std::deque<sf::Vector2i> body;

	Direction direction;

	//P1, P2, computer, etc
	SnakeController controller;

	sf::Vector2i tailPosition;

public:
	Snake(sf::Color color, const std::deque<sf::Vector2i> & body, Direction direction, SnakeController controller);

	int getLength() const;

	sf::Vector2i getBodySegment(int index) const;

	Direction getDirection() const;

	SnakeController getController() const;

	sf::Color getColor() const;

	MoveStatus move(const SolidMap & solidMap);

	void grow();

	void setDirection(Direction direction);

	bool operator==(const Snake & other);
};


#endif
