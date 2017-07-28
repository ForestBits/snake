#include <array>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include "../Utility/Random.h"
#include "MoveValidator.h"
#include "SnakeAI.h"

namespace std 
{
	template <> struct hash<sf::Vector2i>
	{
		size_t operator()(const sf::Vector2i& x) const
		{
			return ((x.x + 5)*x.y) >> 3 + 2;
		}
	};
}

std::vector<sf::Vector2i> getNeighbors(sf::Vector2i position, const SolidMap & map)
{
	std::vector<sf::Vector2i> potentialNeighbors;

	potentialNeighbors.push_back(map.getRelativePosition(position, Direction::RIGHT));
	potentialNeighbors.push_back(map.getRelativePosition(position, Direction::LEFT));
	potentialNeighbors.push_back(map.getRelativePosition(position, Direction::UP));
	potentialNeighbors.push_back(map.getRelativePosition(position, Direction::DOWN));

	std::vector<sf::Vector2i> neighbors;

	for (sf::Vector2i position : potentialNeighbors)
		if (!map.isSolid(position))
			neighbors.push_back(position);

		return neighbors;
}

float valueOfPosition(sf::Vector2i position, sf::Vector2i foodPosition, const SolidMap & map, const std::unordered_map<sf::Vector2i, int> & snakePoints)
{
        /*int xDistance = position.x - foodPosition.x;
        int yDistance = position.y - foodPosition.y;

        float totalDistance = std::sqrt(std::pow(xDistance, 2) + std::pow(yDistance, 2));

        float maxDistance = std::sqrt(std::pow(map.getSize().x, 2) + std::pow(map.getSize().y, 2));

        float distanceValue = (1 - totalDistance/maxDistance)*20;*/

        int xDistance = std::abs(position.x - foodPosition.x);
        int yDistance = std::abs(position.y - foodPosition.y);

        int manhattanDistance = xDistance + yDistance;

        int totalManhattanDistance = map.getSize().x + map.getSize().y;

        float distanceValue = (1 - static_cast<float>(manhattanDistance)/totalManhattanDistance)*20;

        float foodValue;

        if (position == foodPosition)
                foodValue = 1000;
        else
                foodValue = 0;

		float snakeValue = 0;

		if (snakePoints.count(position) > 0)
			snakeValue = -snakePoints.at(position)*25;

        return distanceValue + foodValue + snakeValue;
}

float valueOfPath(sf::Vector2i position, sf::Vector2i foodPosition, const SolidMap & map, const std::unordered_map<sf::Vector2i, int> & snakePoints, std::vector<sf::Vector2i> & visited, int depth, const int maxDepth)
{
        if (depth > maxDepth)
                return 0;

        float value = valueOfPosition(position, foodPosition, map, snakePoints);

        visited.push_back(position);

        auto isVisited = [] (sf::Vector2i position, const std::vector<sf::Vector2i> & visited) {return std::find(visited.begin(), visited.end(), position) != visited.end();};

        float bestValue = -99999;

        auto neighbors = getNeighbors(position, map);

        for (sf::Vector2i neighbor : neighbors)
                if (!isVisited(neighbor, visited))
                {
                        float temporaryValue = valueOfPath(neighbor, foodPosition, map, snakePoints, visited, depth + 1, maxDepth);

                        if (temporaryValue > bestValue)
                                bestValue = temporaryValue;
                }

        value += bestValue;

        return value;
}

void getSnakePoints(std::unordered_map<sf::Vector2i, int> & snakePoints, const SolidMap & map, const sf::Vector2i position, std::vector<sf::Vector2i> & visited, int depth, const int maxDepth)
{
	if (depth == maxDepth)
		return;

	if (std::find(visited.begin(), visited.end(), position) != visited.end())
		return;
	else
		visited.push_back(position);

	if (depth && map.isSolid(position))
		return;

	//if contains
	if (snakePoints.count(position) > 0)
		snakePoints[position] += maxDepth - depth;
	else
		snakePoints[position] = maxDepth - depth;

	if (depth < maxDepth)
	{
		getSnakePoints(snakePoints, map, map.getRelativePosition(position, Direction::RIGHT), visited, depth + 1, maxDepth);
		getSnakePoints(snakePoints, map, map.getRelativePosition(position, Direction::LEFT), visited, depth + 1, maxDepth);
		getSnakePoints(snakePoints, map, map.getRelativePosition(position, Direction::DOWN), visited, depth + 1, maxDepth);
		getSnakePoints(snakePoints, map, map.getRelativePosition(position, Direction::UP), visited, depth + 1, maxDepth);
	}
}

Direction getMove(AiDifficulty difficulty, const SolidMap & walls, const std::vector<Snake> & snakes, sf::Vector2i headPosition, sf::Vector2i foodPosition)
{
        SolidMap combined(walls);

        for (const Snake & snake : snakes)
			for (int i = 0; i < snake.getLength(); ++i)
				combined.setSolid(snake.getBodySegment(i), true);

		std::unordered_map<sf::Vector2i, int> snakePoints;

		std::vector<sf::Vector2i> visited;

		std::vector<sf::Vector2i> headPositions;
		
		for (const Snake & snake : snakes)
			if (snake.getBodySegment(0) != headPosition)
				headPositions.push_back(snake.getBodySegment(0));

		for (int i = 0; i < headPositions.size(); ++i)
			getSnakePoints(snakePoints, combined, headPositions[i], visited, 0, 4);

        int searchDepth = 5;

        std::unordered_map<Direction, float> values;

        sf::Vector2i rightPosition = combined.getRelativePosition(headPosition, Direction::RIGHT);
        sf::Vector2i leftPosition = combined.getRelativePosition(headPosition, Direction::LEFT);
        sf::Vector2i upPosition = combined.getRelativePosition(headPosition, Direction::UP);
        sf::Vector2i downPosition = combined.getRelativePosition(headPosition, Direction::DOWN);

		if (rightPosition == foodPosition)
			return Direction::RIGHT;
		else if (leftPosition == foodPosition)
			return Direction::LEFT;
		else if (downPosition == foodPosition)
			return Direction::DOWN;
		else if (upPosition == foodPosition)
			return Direction::UP;

        values[Direction::RIGHT] = combined.isSolid(rightPosition) ? -99999 : valueOfPath(rightPosition, foodPosition, combined, snakePoints, visited, 0, searchDepth);

        visited.clear();

        values[Direction::LEFT] = combined.isSolid(leftPosition) ? -99999 : valueOfPath(leftPosition, foodPosition, combined, snakePoints, visited, 0, searchDepth);

        visited.clear();

        values[Direction::DOWN] = combined.isSolid(downPosition) ? -99999 : valueOfPath(downPosition, foodPosition, combined, snakePoints, visited, 0, searchDepth);

        visited.clear();

        values[Direction::UP] = combined.isSolid(upPosition) ? -99999 : valueOfPath(upPosition, foodPosition, combined, snakePoints, visited, 0, searchDepth);

        std::pair<Direction, float> best;

        best.first = Direction::RIGHT;
        best.second = -9999;

        for (auto pair : values)
                if (pair.second > best.second)
                        best = pair;

		if (combined.isSolid(combined.getRelativePosition(headPosition, best.first)))
		{
			std::vector<int> ints;

			for (int i = 0; i < 5; ++i)
				ints.push_back(i*5/2);

			if (ints[2] == 10)
				return Direction::UP;
		}

        return best.first;
}