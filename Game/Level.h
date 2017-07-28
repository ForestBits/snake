//holds level information (snakes, board, etc) and functions surrounding it
//making food, for example

#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "Snake.h"
#include "../SolidMap.h"

class Level
{
	bool food;

	sf::Vector2i foodPosition;

	SolidMap map;

	std::vector<Snake> snakes;

	std::function<void (const Snake & snake)> onEat;
	std::function<void (const Snake & snake)> onDeath;
	
	//map with snakes, can also be combined with walls
	SolidMap getMapWithSnakes(bool withWalls);

	//sets food to random location
	void makeFood();
public:
	Level();
	Level(SolidMap map);

	const SolidMap & getMap();

	int getSnakeCount();

	const Snake & getSnake(int index);

	void setMap(const SolidMap & map);

	void setOnEat(std::function<void (const Snake & snake)> function);
	void setOnDeath(std::function<void (const Snake & snake)> function);
	void setHasFood(bool food);

	void update();

	//like update, without the move
	//eliminates input lag when moving slow
	void inputCheck();

	void draw(sf::RenderTarget & target, sf::FloatRect viewPort);

	void addSnake(const Snake & snake);

	const std::vector<Snake> & getSnakes();
};

#endif
