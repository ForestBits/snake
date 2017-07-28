#include <fstream>
#include <cstdio>
#include <algorithm>
#include "../Utility/StringNumberConvert.h"
#include "SaveOperations.h"

void writeScore(std::string fileName, std::pair<std::string, int> score)
{
	std::fstream file;

	file.open(fileName.c_str(), std::ios::out | std::ios::app);

	file << score.first << ":" << toString(score.second) << std::endl;
}

std::vector<std::pair<std::string, int>> getScores(std::string fileName, int count)
{
	std::vector<std::pair<std::string, int>> scores;

	std::fstream file;

	file.open(fileName.c_str(), std::ios::in);

	std::string line;

	while (std::getline(file, line))
	{
		if (file.bad() || file.eof())
			break;

		std::string name = line.substr(0, line.find(':'));

		int score = toNumber<int>(line.substr(line.find(':') + 1));

		scores.push_back(std::make_pair(name, score));
	}

	std::sort(scores.begin(), scores.end(), [] (const std::pair<std::string, int> & score1, const std::pair<std::string, int> & score2) {return score1.second > score2.second;});

	std::vector<std::pair<std::string, int>> someScores;

	int scoreCount = count > scores.size() ? scores.size() : count;

	for (int i = 0; i < scoreCount; ++i)
		someScores.push_back(scores[i]);

	return someScores;
}

void clearScores(std::string fileName)
{
	remove(fileName.c_str());
}