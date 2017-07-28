#include "../Utility/Random.h"
#include "CircleGenerator.h"

SolidMap generateCircles(int width, int height, int margin, int circleCount, float radius, float radiusVariation)
{
	Random random;

	SolidMap map(width, height);

	int maxRadius = std::ceil(radius + radiusVariation);

	for (int i = 0; i < circleCount; ++i)
	{
		int circleX = random.iRandomRange(margin + maxRadius, width - (margin + maxRadius + 1));
		int circleY = random.iRandomRange(margin + maxRadius, height - (margin + maxRadius + 1));

		float circleRadius = radius + (random.nextBool() ? random.nextDouble()*radiusVariation : -random.nextDouble()*radiusVariation);

		for (int x = circleX - circleRadius; x < circleX + std::ceil(circleRadius); ++x)
			for (int y = circleY - circleRadius; y < circleY + std::ceil(circleRadius); ++y)
			{
				int xDistance = std::abs(circleX - x);
				int yDistance = std::abs(circleY - y);

				double distance = std::sqrt(std::pow(xDistance, 2) + std::pow(yDistance, 2));

				if (distance < circleRadius)
					map.setSolid(x, y, true);
			}
	}

	return map;
}