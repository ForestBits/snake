#include <cassert>
#include "Snake.h"

Snake::Snake(sf::Color color, const std::deque<sf::Vector2i> & body, Direction direction, SnakeController controller) : color(color), body(body), direction(direction), controller(controller), tailPosition(body[body.size() - 1])
{

}

int Snake::getLength() const
{
	return body.size();
}

sf::Color Snake::getColor() const
{
	return color;
}

Direction Snake::getDirection() const
{
	return direction;
}

SnakeController Snake::getController() const
{
	return controller;
}

sf::Vector2i Snake::getBodySegment(int index) const
{
	assert(index >= 0 && index < body.size());

	return body[index];
}

void Snake::setDirection(Direction direction)
{
	this->direction = direction;
}

void Snake::grow()
{
	body.push_back(tailPosition);
}

MoveStatus Snake::move(const SolidMap & solidMap)
{
	tailPosition = body.back();

	sf::Vector2i nextPosition = solidMap.getRelativePosition(body.front(), direction);

	body.push_front(nextPosition);

	body.pop_back();

	return solidMap.isSolid(nextPosition.x, nextPosition.y) ? MoveStatus::HIT_WALL : MoveStatus::SUCCESS;
}

bool Snake::operator==(const Snake & other)
{
	return (this->body == other.body && this->color == other.color && this->controller == other.controller && this->direction == other.direction);
}
