#include <cassert>
#include "RandomInteriorBlocksGenerator.h"
#include "../Utility/Random.h"


SolidMap generateRandomInteriorBlocks(int width, int height, int margin, float fillPercent)
{
	assert(fillPercent >= 0 && fillPercent <= 1);

	SolidMap solidMap(width, height);

	//we want some empty area around the edges (e.g. where the snakes start)
	//so blocks will only be generated a bit away from the edges (by margin)

	int avaliableArea = (width - margin)*(height - margin);

	int blocksToFill = fillPercent*avaliableArea;

	Random random;

	for (int i = 0; i < blocksToFill; ++i)
	{
		bool done = false;

		while (!done)
		{
			int randomX = random.iRandomRange(margin, width - (margin + 1));
			int randomY = random.iRandomRange(margin, height - (margin + 1));

			if (solidMap.isSolid(randomX, randomY))
				continue;

			solidMap.setSolid(randomX, randomY, true);

			done = true;
		}
	}

	for (int x = 0; x < solidMap.getSize().x; ++x)
		for (int y = 0; y < solidMap.getSize().y; ++y)
		{
			if (!solidMap.isSolid(x, y))
			{
				int touchCount = 0;

				if (x - 1 >= 0 && solidMap.isSolid(x - 1, y))
					++touchCount;

				if (x + 1 < solidMap.getSize().x && solidMap.isSolid(x + 1, y))
					++touchCount;

				if (y - 1 >= 0 && solidMap.isSolid(x, y - 1))
					++touchCount;

				if (y + 1 < solidMap.getSize().y && solidMap.isSolid(x, y + 1))
					++touchCount;

				if (touchCount > 1)
					solidMap.setSolid(x, y, true);
			}
		}

	return solidMap;
}