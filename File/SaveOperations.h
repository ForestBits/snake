//save score, get list of scores, etc etc

#ifndef SAVEOPERATIONS_H
#define SAVEOPERATIONS_H

#include <string>
#include <vector>

//scores are a pair of name/initial/identifier and score
void writeScore(std::string fileName, std::pair<std::string, int> score);

//pre-sorted, highest first
std::vector<std::pair<std::string, int>> getScores(std::string fileName, int count);

//deletes file, note this cannot be undone
void clearScores(std::string fileName);

#endif
