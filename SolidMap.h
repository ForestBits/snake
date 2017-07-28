//2D maps of solids (blocks light), and non-solids (light passes through

#ifndef SOLIDMAP_H
#define SOLIDMAP_H

#include <SFML/System.hpp>
#include <vector>
#include "Utility/DimensionalIndex.h"
#include "Game/Direction.h"


class SolidMap
{
	std::vector<bool> solid;

	sf::Vector2i size;

public:
	SolidMap();
	SolidMap(int width, int height);
	SolidMap(sf::Vector2i size);

	bool isSolid(int x, int y) const;
	bool isSolid(sf::Vector2i position) const;

	sf::Vector2i getSize() const;

	void setSolid(int x, int y, bool solid);
	void setSolid(sf::Vector2i, bool solid);

	void setSize(int x, int y);
	void setSize(sf::Vector2i size);

	sf::Vector2i getRelativePosition(sf::Vector2i position, Direction direction) const;
};


#endif
