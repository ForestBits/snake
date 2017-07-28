#include <cassert>
#include "../Utility/Random.h"
#include "MoveValidator.h"
#include "Level.h"
#include "SnakeAI.h"

Level::Level()
{

}

Level::Level(SolidMap map) : map(map)
{
	makeFood();
}

void Level::makeFood()
{
	Random random;

	std::vector<sf::Vector2i> emptyBlocks;

	for (int x = 0; x < map.getSize().x; ++x)
		for (int y = 0; y < map.getSize().y; ++y)
			if (!map.isSolid(x, y))
				emptyBlocks.push_back(sf::Vector2i(x, y));

	for (const Snake & snake : snakes)
		for (int i = 0; i < snake.getLength(); ++i)
			for (sf::Vector2i position : emptyBlocks)
				if (snake.getBodySegment(i) == position)
				{
					emptyBlocks.erase(std::find(emptyBlocks.begin(), emptyBlocks.end(), position));

					break;
				}
	
	std::vector<sf::Vector2i> toRemove;

	for (sf::Vector2i position : emptyBlocks)
	{
		int touchCount = 0;

		if (position.x > 0 && !map.isSolid(position.x - 1, position.y))
			++touchCount;

		if (position.y > 0 && !map.isSolid(position.x, position.y -1))
			++touchCount;

		if (position.x + 1 < map.getSize().x && !map.isSolid(position.x + 1, position.y))
			++touchCount;

		if (position.y + 1 < map.getSize().y && !map.isSolid(position.x, position.y + 1))
			++touchCount;

		//if the route to the food is a dead end, don't consider it
		if (touchCount < 2)
			toRemove.push_back(position);
	}

	for (sf::Vector2i remove : toRemove)
		emptyBlocks.erase(std::find(emptyBlocks.begin(), emptyBlocks.end(), remove));

	foodPosition = emptyBlocks[random.nextInt(emptyBlocks.size())];
}

SolidMap Level::getMapWithSnakes(bool withWalls)
{
	SolidMap snakeMap;

	if (withWalls)
		snakeMap = map;
	else
		snakeMap.setSize(map.getSize());

	for (Snake snake : snakes)
		for (int i = 0; i < snake.getLength(); ++i)
			snakeMap.setSolid(snake.getBodySegment(i).x, snake.getBodySegment(i).y, true);

	return snakeMap;
}

const SolidMap & Level::getMap()
{
	return map;
}

int Level::getSnakeCount()
{
	return snakes.size();
}

const Snake & Level::getSnake(int index)
{
	assert(index >= 0 && index < snakes.size());

	return snakes[index];
}

const std::vector<Snake> & Level::getSnakes()
{
	return snakes;
}

void Level::setOnEat(std::function<void (const Snake & snake)> function)
{
	onEat = function;
}

void Level::setOnDeath(std::function<void (const Snake & snake)> function)
{
	onDeath = function;
}

void Level::setMap(const SolidMap & map)
{
	this->map = map;

	makeFood();
}

void Level::setHasFood(bool food)
{
	if (!food)
		foodPosition = sf::Vector2i(-1, -1);
	else
		makeFood();
}

void Level::update()
{
	std::vector<Snake> toRemove;

	SolidMap snakeMap = getMapWithSnakes(true);

	for (Snake & snake : snakes)
	{
		SnakeController controller = snake.getController();

		switch (controller)
		{
		case SnakeController::PLAYER_1:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && validateMove(snakeMap, snake.getBodySegment(0), Direction::LEFT))
				snake.setDirection(Direction::LEFT);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && validateMove(snakeMap, snake.getBodySegment(0), Direction::RIGHT))
				snake.setDirection(Direction::RIGHT);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && validateMove(snakeMap, snake.getBodySegment(0), Direction::DOWN))
				snake.setDirection(Direction::DOWN);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && validateMove(snakeMap, snake.getBodySegment(0), Direction::UP))
				snake.setDirection(Direction::UP);

			break;

		case SnakeController::PLAYER_2:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && validateMove(snakeMap, snake.getBodySegment(0), Direction::LEFT))
				snake.setDirection(Direction::LEFT);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && validateMove(snakeMap, snake.getBodySegment(0), Direction::RIGHT))
				snake.setDirection(Direction::RIGHT);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && validateMove(snakeMap, snake.getBodySegment(0), Direction::DOWN))
				snake.setDirection(Direction::DOWN);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && validateMove(snakeMap, snake.getBodySegment(0), Direction::UP))
				snake.setDirection(Direction::UP);

			break;

		case SnakeController::COMPUTER:
			snake.setDirection(getMove(AiDifficulty::EASY, map, snakes, snake.getBodySegment(0), foodPosition));

			break;
		}

		if (snake.move(snakeMap) == MoveStatus::HIT_WALL)
			toRemove.push_back(snake);

		if (snake.getBodySegment(0).x == foodPosition.x && snake.getBodySegment(0).y == foodPosition.y)
		{
			snake.grow();

			makeFood();

			if (onEat)
				onEat(snake);
		}
	}

	for (const Snake & snake : toRemove)
	{
		if (snakeMap.isSolid(snake.getBodySegment(0).x, snake.getBodySegment(0).y))
		{
			if (onDeath)
				onDeath(snake);

			snakes.erase(std::find(snakes.begin(), snakes.end(), snake));
		}
	}
}

void Level::inputCheck()
{
	SolidMap snakeMap = getMapWithSnakes(true);

	for (Snake & snake : snakes)
	{
		SnakeController controller = snake.getController();

		switch (controller)
		{
		case SnakeController::PLAYER_1:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && validateMove(snakeMap, snake.getBodySegment(0), Direction::LEFT))
				snake.setDirection(Direction::LEFT);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && validateMove(snakeMap, snake.getBodySegment(0), Direction::RIGHT))
				snake.setDirection(Direction::RIGHT);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && validateMove(snakeMap, snake.getBodySegment(0), Direction::DOWN))
				snake.setDirection(Direction::DOWN);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && validateMove(snakeMap, snake.getBodySegment(0), Direction::UP))
				snake.setDirection(Direction::UP);

			break;

		case SnakeController::PLAYER_2:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && validateMove(snakeMap, snake.getBodySegment(0), Direction::LEFT))
				snake.setDirection(Direction::LEFT);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && validateMove(snakeMap, snake.getBodySegment(0), Direction::RIGHT))
				snake.setDirection(Direction::RIGHT);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && validateMove(snakeMap, snake.getBodySegment(0), Direction::DOWN))
				snake.setDirection(Direction::DOWN);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && validateMove(snakeMap, snake.getBodySegment(0), Direction::UP))
				snake.setDirection(Direction::UP);

			break;

		case SnakeController::COMPUTER:
			snake.setDirection(getMove(AiDifficulty::EASY, map, snakes, snake.getBodySegment(0), foodPosition));

			break;
		}
	}
}

//note: the floatrect argument is like SFML's viewports, it is expressed as a fraction of the window size
void Level::draw(sf::RenderTarget & target, sf::FloatRect viewPort)
{
	assert(viewPort.left >= 0 && viewPort.left < 1 && viewPort.top >= 0 && viewPort.top < 1 && viewPort.width < 1 - viewPort.left && viewPort.height < 1 - viewPort.top);

	sf::IntRect bounds;

	bounds.left = viewPort.left*target.getSize().x;
	bounds.top = viewPort.top*target.getSize().y;
	
	bounds.width = viewPort.width*target.getSize().x;
	bounds.height = viewPort.height*target.getSize().y;

	int blockSize = bounds.width/map.getSize().x;

	if (map.getSize().y*blockSize > bounds.height)
		blockSize = bounds.height/map.getSize().y;

	sf::Vector2i offset;

	offset.x = (bounds.width - (map.getSize().x*blockSize))/2;
	offset.y = (bounds.height - (map.getSize().y*blockSize))/2;

	sf::RectangleShape rectangle(sf::Vector2f(blockSize, blockSize));

	sf::RectangleShape outline;
	outline.setFillColor(sf::Color::Transparent);
	outline.setOutlineThickness(1);
	outline.setOutlineColor(sf::Color::Black);
	outline.setPosition(bounds.left + offset.x, bounds.top + offset.y);
	outline.setSize(sf::Vector2f(map.getSize().x*blockSize, map.getSize().y*blockSize));

	std::vector<std::vector<sf::Color>> colors;

	colors.resize(map.getSize().x);

	for (int x = 0; x < map.getSize().x; ++x)
		colors[x].resize(map.getSize().y);

	for (int x = 0; x < map.getSize().x; ++x)
		for (int y = 0; y < map.getSize().y; ++y)
		{
			if (map.isSolid(x, y))
				colors[x][y] = sf::Color::Black;
			else
				colors[x][y] = sf::Color::White;

			if (foodPosition.x == x && foodPosition.y == y)
				colors[x][y] = sf::Color::Yellow;
		}

	for (const Snake & snake : snakes)
		for (int i = 0; i < snake.getLength(); ++i)
			colors[snake.getBodySegment(i).x][snake.getBodySegment(i).y] = snake.getColor();

	for (int x = 0; x < map.getSize().x; ++x)
		for (int y = 0; y < map.getSize().y; ++y)
		{
			rectangle.setPosition(bounds.left + offset.x + x*blockSize, bounds.top + offset.y + ((map.getSize().y - y)*blockSize) - blockSize);

			rectangle.setFillColor(colors[x][y]);

			target.draw(rectangle);
		}

	target.draw(outline);
}

void Level::addSnake(const Snake & snake)
{
	snakes.push_back(snake);
}