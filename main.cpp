#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Glass.h"
#include "Misc.h"

// Need to pass by value to avoid polluting input ray
Vec3f DetermineColor(Rayf ray, Hitable* world, int depth)
{
	HitRecord_t rec;
	if(world->Hit(ray, 0.001f, FLT_MAX, rec))
	{ 
		Rayf scattered;
		Vec3f attenuation;
		if (depth < 50
			&& rec.matPtr->Scatter(ray, rec, attenuation, scattered))
		{
			// TODO: Double check how tail end recursion works and whether this call can be optimized
			Vec3f color = DetermineColor(scattered, world, depth + 1);
			return Vec3f(attenuation.x * color.x,
						 attenuation.y * color.y,
				         attenuation.z * color.z);
		}
		else
		{
			return Vec3f(0,0,0);
		}
	}
	else
	{
		float t = 0.5f * (ray.dir.Normalize().y + 1);
		return (1 - t) * Vec3f(1.0f, 1.0f, 1.0f) + t * Vec3f(0.5f, 0.7f, 1.0f);
	}
}

int main()
{
	/* initialize random seed: */
	srand(time(NULL));

	std::ofstream ppmFile("out.ppm");
	ppmFile << "P3\n";

	int nCols = 200;
	int nRows = 100;
	int nRaysPerPixel = 100;
	ppmFile << nCols << " " << nRows <<"\n255\n";

	Vec3f lookFrom(3, 3, 2);
	Vec3f lookAt(0, 0, -1);
	float focalLength = (lookFrom - lookAt).GetMagnitude();
	float aperture = 2.0f;

	Camera camera(lookFrom, lookAt, Vec3f(0,1,0), 30, float(nCols) / float(nRows), aperture, focalLength);

	std::vector<Hitable*> hitList;
	hitList.push_back(new Sphere(Vec3f(0, 0, -1),      0.5f, new Lambertian(Vec3f(0.8f, 0.3f, 0.3f))));
	hitList.push_back(new Sphere(Vec3f(0, -100.5, -1), 100,  new Lambertian(Vec3f(0.8f, 0.8f, 0.0f))));
	hitList.push_back(new Sphere(Vec3f(1, 0, -1),      0.5f, new Metal(Vec3f(0.8f, 0.6f, 0.2f), 0.3f)));
	hitList.push_back(new Sphere(Vec3f(-1, 0, -1),     0.5f, new Glass(1.5f)));
	hitList.push_back(new Sphere(Vec3f(-1, 0, -1),   -0.45f, new Glass(1.5f)));

	Hitable *world = new HitableList(hitList, hitList.size());

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

				color += DetermineColor(ray, world, 0);
			}

			// Average the individual color values determined by each ray to blend into the final pixel color
			color /= float(nRaysPerPixel);
			color = Vec3f(sqrt(color.r), sqrt(color.g), sqrt(color.b));

			// Convert from 0-1 range back to 0-255 range
			// Leaving float results in small numbers, not multiplying by 255.9 results in all 0
			Vec3i rgbScaled(255.9*color.r,
							255.9*color.g,
							255.9*color.b);

			ppmFile << rgbScaled.r << " " << rgbScaled.g << " " << rgbScaled.b << "\n";
		}
	}

	delete world;

	return 0;
}