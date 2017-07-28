#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random
{
	std::default_random_engine engine;

public:
	Random();
	Random(long seed);

	bool nextBool();
	
	int nextInt();
	int nextInt(int n); //[0, n)

	float nextFloat(); //[0, 1]

	double nextDouble(); //[0, 1]

	void setSeed(long seed);

	int randomRange(int lowerBound, int upperBound); //[lowerBound, upperBound)

	int iRandomRange(int lowerBound, int upperBound); //[lowerBound, upperBound]
};


#endif
