//these are utilities to convert multiple dimensions to a single dimension, similar to "fake arrays"


#ifndef DIMENSIONALINDEX_H
#define DIMENSIONALINDEX_H

class Index2D
{
	int sizeY;

public:
	inline Index2D(int sizeY) : sizeY(sizeY) {}

	inline int operator() (int x, int y) {return sizeY * x + y;}

	inline int index(int x, int y) {return sizeY * x + y;}
};

class Index3D
{
	int sizeX;
	int sizeY;

public:
	inline Index3D(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY) {}

	inline int operator() (int x, int y, int z) {return x + y * sizeX + z * sizeX * sizeY;}

	inline int index(int x, int y, int z) {return x + y * sizeX + z * sizeX * sizeY;}
};

#endif
