//validates moves - for example, a snake cannot turn into itself

#ifndef MOVEVALIDATOR_H
#define MOVEVALIDATOR_h

#include "../SolidMap.h"
#include "Snake.h"
#include "Direction.h"

bool validateMove(const SolidMap & map, sf::Vector2i position, Direction direction);

#endif
