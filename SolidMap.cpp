#include <cassert>
#include "SolidMap.h"
#include "Utility/DimensionalIndex.h"

SolidMap::SolidMap() {}

SolidMap::SolidMap(int x, int y) : size(x, y), solid(x*y, false) 
{
	assert(x >= 0 && y >= 0);
}

SolidMap::SolidMap(sf::Vector2i size) : SolidMap(size.x, size.y) {}

bool SolidMap::isSolid(int x, int y) const
{
	Index2D i(size.y);

	assert(x >= 0 && y >= 0 && x < size.x && y < size.y);

	return solid[i(x, y)];
}

bool SolidMap::isSolid(sf::Vector2i position) const
{
	return isSolid(position.x, position.y);
}

void SolidMap::setSolid(int x, int y, bool isSolid)
{
	Index2D i(size.y);

	assert(x >= 0 && y >= 0 && x < size.x && y < size.y);

	solid[i(x, y)] = isSolid;
}

void SolidMap::setSolid(sf::Vector2i position, bool isSolid)
{
	setSolid(position.x, position.y, isSolid);
}

sf::Vector2i SolidMap::getSize() const
{
	return size;
}

void SolidMap::setSize(int x, int y)
{
	setSize(sf::Vector2i(x, y));
}

void SolidMap::setSize(sf::Vector2i size)
{
	this->size = size;

	Index2D i(size.y);

	solid.resize(size.x*size.y);

	for (int x = 0; x < size.x; ++x)
		for (int y = 0; y < size.y; ++y)
			solid[i(x, y)] = false;
}

sf::Vector2i SolidMap::getRelativePosition(sf::Vector2i position, Direction direction) const
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
                position.x = getSize().x - 1;

        if (position.x >= getSize().x)
                position.x = 0;

        if (position.y < 0)
                position.y = getSize().y - 1;

        if (position.y >= getSize().y)
                position.y = 0;

        return position;
}