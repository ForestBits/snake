#include "WalledGenerator.h"

SolidMap generateWalled(int width, int height)
{
	SolidMap map(width, height);

	for (int x = 0; x < width; ++x)
	{
		map.setSolid(x, 0, true);
		map.setSolid(x, height - 1, true);
	}

	for (int y = 0; y < height; ++y)
	{
		map.setSolid(0, y, true);
		map.setSolid(width - 1, y, true);
	}

	return map;
}