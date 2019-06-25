#include <iostream>
#include <fstream>
#include <string>

#include "Vec3.h"
#include "Ray.h"

Vec3f DetermineColor(const Rayf& ray)
{
	Vec3f rayDir = ray.dir;
	float t = 0.5f * (rayDir.Normalize().y + 1);
	return (1 - t) * Vec3f(1.0f, 1.0f, 1.0f) + t * Vec3f(0.5f, 0.7f, 1.0f);
}

int main()
{
	std::ofstream ppmFile("out.ppm");
	ppmFile << "P3\n";

	int nCols = 200;
	int nRows = 100;
	ppmFile << nCols << " " << nRows <<"\n255\n";

	// Define points in box
	Vec3f lowerLeftCorner(-2, -1, -1);
	Vec3f horizontal(4, 0, 0);
	Vec3f vertical(0, 2, 0);
	Vec3f origin(0, 0, 0);

	// Write pixels left to write and bottom to top
	for (int j = nRows - 1; j >= 0; j--)
	{
		for (int i = 0; i < nCols; i++)
		{
			// Convert rgb to a val between 0 and 1
			float u = i / float(nCols);
			float v = j / float(nRows);

			// Ray from origin to top right corner of box
			Rayf ray(origin, lowerLeftCorner + u * horizontal + v * vertical);

			// Convert from 0-1 range back to 0-255 range
			// Leaving float results in small numbers, not multiplying by 
			// 255.9 results in all 0
			Vec3f color = DetermineColor(ray);
			Vec3i rgbBetween0And255(255.9*color.r,
									255.9*color.g,
									255.9*color.b);

			ppmFile << rgbBetween0And255.r << " " << rgbBetween0And255.g << " " << rgbBetween0And255.b << "\n";
		}
	}

	return 0;
}