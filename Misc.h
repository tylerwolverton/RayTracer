#pragma once
#include <time.h>

#include "Vec3.h"

// If I was a better programmer I'd encapsulate all these methods into well 
// organized classes but hey, what can you do?

float randf01()
{
	return float(rand() % 100) / 100;
}

// Find point in unit cube and reject if not in sphere
Vec3f GetRandomVectorInUnitSphere()
{
	Vec3f p;
	do {
		p = 2.0 * Vec3f(randf01(), randf01(), randf01()) - Vec3f(1, 1, 1);
	} while (p.GetSquaredMagnitude() >= 1);

	return p;
}