#include "MoveValidator.h"

bool validateMove(const SolidMap & map, sf::Vector2i position, Direction direction)
{
	switch (direction)
	{
	case Direction::LEFT:
		--position.x;

		break;

	case Direction::RIGHT:
		++position.x;

		break;

	case Direction::UP:
		++position.y;

		break;

	case Direction::DOWN:
		--position.y;

		break;
	}

	if (position.x < 0)
		position.x = map.getSize().x - 1;

	if (position.x >= map.getSize().x)
		position.x = 0;

	if (position.y < 0)
		position.y = map.getSize().y - 1;

	if (position.y >= map.getSize().y)
		position.y = 0;

	return (!map.isSolid(position.x, position.y));
}