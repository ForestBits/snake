#include "../Utility/Random.h"
#include "RandomScatteredBlocksGenerator.h"

SolidMap generateRandomScatteredBlocks(int width, int height, int margin, float fillPercent)
{
	Random random;

	SolidMap map(width, height);

	int blockCount = fillPercent*(width - margin*2)*(height - margin*2);

	for (int i = 0; i < blockCount; ++i)
	{
		for (int tries = 0; tries < 10; ++tries)
		{
			int randomX = random.iRandomRange(margin, width - (margin + 1));
			int randomY = random.iRandomRange(margin, height - (margin + 1));

			if (map.isSolid(randomX, randomY))
				continue;
			
			int touchCount = 0;

				if (randomX - 1 >= 0 && map.isSolid(randomX - 1, randomY))
					++touchCount;

				if (randomX + 1 < map.getSize().x && map.isSolid(randomX + 1, randomY))
					++touchCount;

				if (randomY - 1 >= 0 && map.isSolid(randomX, randomY - 1))
					++touchCount;

				if (randomY + 1 < map.getSize().y && map.isSolid(randomX, randomY + 1))
					++touchCount;

				if (randomX - 1 >= 0 && randomY - 1 >= 0 && map.isSolid(randomX - 1, randomY - 1))
					++touchCount;

				if (randomX + 1 < map.getSize().x && randomY - 1 >= 0 && map.isSolid(randomX + 1, randomY - 1))
					++touchCount;

				if (randomX - 1 >= 0 && randomY + 1 < map.getSize().y && map.isSolid(randomX - 1, randomY + 1))
					++touchCount;

				if (randomX + 1 < map.getSize().x && randomY + 1 < map.getSize().y && map.isSolid(randomX + 1, randomY + 1))
					++touchCount;

				if (touchCount == 0)
					map.setSolid(randomX, randomY, true);
		}
	}

	return map;
}