#include "Random.h"
#include <ctime>
#include <iostream>

Random::Random()
{
	std::random_device device;

	engine.seed(device());
}

Random::Random(long seed)
{
	engine.seed(seed);
}

bool Random::nextBool()
{
	std::uniform_int_distribution<int> distribution(0, 1);

	return distribution(engine) != 0;
}

int Random::nextInt()
{
	return engine();
}

int Random::nextInt(int n)
{
	std::uniform_int_distribution<int> distribution(0, n - 1);

	return distribution(engine);
}


float Random::nextFloat()
{
	std::uniform_real_distribution<float> distribution(0.f, 1.f);

	return distribution(engine);
}

double Random::nextDouble()
{
	std::uniform_real_distribution<float> distribution(0.f, 1.f);

	return distribution(engine);
}

void Random::setSeed(long seed)
{
	engine.seed(seed);
}

int Random::randomRange(int lowerBound, int upperBound)
{
	return nextInt((upperBound) - lowerBound) + lowerBound;
}

int Random::iRandomRange(int lowerBound, int upperBound)
{
	return nextInt((upperBound + 1) - lowerBound) + lowerBound;
}