#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"

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

// Need to pass by value to avoid polluting input ray
Vec3f DetermineColor(Rayf ray, Hitable* world)
{
	HitRecord_t rec;
	if(world->Hit(ray, 0.001f, FLT_MAX, rec))
	{ 
		// Target is a random point in the sphere centered on the point 1 unit
		// away along the normal from the hit point, p
		Vec3f target = rec.p + rec.normal + GetRandomVectorInUnitSphere();
		// Return half intensity of the color found at reflected target location
		return 0.5f * DetermineColor(Rayf(rec.p, target - rec.p), world);
	}
	else
	{
		float t = 0.5f * (ray.dir.Normalize().y + 1);
		return (1 - t) * Vec3f(1.0f, 1.0f, 1.0f) + t * Vec3f(0.5f, 0.7f, 1.0f);
	}
}

int main()
{
	std::ofstream ppmFile("out.ppm");
	ppmFile << "P3\n";

	int nCols = 200;
	int nRows = 100;
	int nRaysPerPixel = 100;
	ppmFile << nCols << " " << nRows <<"\n255\n";

	Camera camera;

	std::vector<Hitable*> hitList;
	hitList.push_back(new Sphere(Vec3f(0, 0, -1), 0.5f));
	hitList.push_back(new Sphere(Vec3f(0, -100.5, -1), 100));

	Hitable *world = new HitableList(hitList, 2);
	/* initialize random seed: */
	srand(time(NULL));

	// Write pixels left to write and bottom to top
	for (int j = nRows - 1; j >= 0; j--)
	{
		for (int i = 0; i < nCols; i++)
		{
			Vec3f color(0, 0, 0);
			for (int s = 0; s < nRaysPerPixel; s++)
			{
				// Convert rgb to a val between 0 and 1
				// Also, randomly distribute the ray between this pixel and the next to remove aliasing
				// The rand will add something onto the "beginning" of this pixel, then dividing by total number
				// converts to a value between 0 and 1, eventually representing all the pixels for a row/column evenly spaced between 0 and 1
				float u = (float(i) + randf01()) / float(nCols);
				float v = (float(j) + randf01()) / float(nRows);

				// Ray from origin to current pixel
				Rayf ray(camera.GetRay(u, v));

				// Convert from 0-1 range back to 0-255 range
				// Leaving float results in small numbers, not multiplying by 
				// 255.9 results in all 0
				color += DetermineColor(ray, world);
			}

			// Average the individual color values determined by each ray to blend into the final pixel color
			color /= float(nRaysPerPixel);
			color = Vec3f(sqrt(color.r), sqrt(color.g), sqrt(color.b));
			Vec3i rgbScaled(255.9*color.r,
							255.9*color.g,
							255.9*color.b);

			ppmFile << rgbScaled.r << " " << rgbScaled.g << " " << rgbScaled.b << "\n";
		}
	}

	return 0;
}