#include "TunneledGenerator.h"
#include "../Utility/Random.h"

SolidMap generateTunneled(int width, int height, int margin, int tunnelCount)
{
	SolidMap map(width, height);

	//outside walls

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

	//inner chunk

	int left = margin + 1;
	int right = width - (margin + 2);
	int top = margin + 1;
	int bottom = height - (margin + 2);

	for (int x = left; x <= right; ++x)
		for (int y = top; y <= bottom; ++y)
			map.setSolid(x, y, true);

	Random random;

	for (int i = 0; i < tunnelCount; ++i)
	{
		bool vertical = random.nextBool();

		if (vertical)
		{
			int randomX = random.nextInt(right - left);

			for (int y = top; y <= bottom; ++y)
				map.setSolid(randomX + left, y, false);
		}
		else
		{
			int randomY = random.nextInt(bottom - top);

			for (int x = left; x <= right; ++x)
				map.setSolid(x, randomY + top, false);
		}
	}

	return map;
}