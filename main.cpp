#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"

// Need to pass by value to avoid polluting input ray
Vec3f DetermineColor(Rayf ray, Hitable* world)
{
	HitRecord_t rec;
	if(world->Hit(ray, 0.0, FLT_MAX, rec))
	{ 
		// Maps from -1 - 1 to 0 - 1 by adding 1 and dividing by 2
		return 0.5f * Vec3f(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1);
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
				// Convert rgb to a val between 0 and 1, randomly distributed in the pixel area to remove aliasing
				float u = (float(i) + float(rand() % 100) / 100) / float(nCols);
				float v = (float(j) + float(rand() % 100) / 100) / float(nRows);

				// Ray from origin to current pixel
				Rayf ray(camera.GetRay(u, v));

				// Convert from 0-1 range back to 0-255 range
				// Leaving float results in small numbers, not multiplying by 
				// 255.9 results in all 0
				color += DetermineColor(ray, world);
			}

			color /= float(nRaysPerPixel);
			Vec3i rgbScaled(255.9*color.r,
							255.9*color.g,
							255.9*color.b);

			ppmFile << rgbScaled.r << " " << rgbScaled.g << " " << rgbScaled.b << "\n";
		}
	}

	return 0;
}