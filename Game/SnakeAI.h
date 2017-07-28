#ifndef SNAKEAI_H
#define SNAKEAI_H

#include "AiDifficulty.h"
#include "../SolidMap.h"
#include "Snake.h"

Direction getMove(AiDifficulty difficulty, const SolidMap & walls, const std::vector<Snake> & snakes, sf::Vector2i headPosition, sf::Vector2i foodPosition);




#endif
