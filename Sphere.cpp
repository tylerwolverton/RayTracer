#include "Sphere.h"

#include <math.h>

bool Sphere::Hit(const Rayf& ray, float tMin, float tMax, HitRecord_t& rec) const
{
	// Sphere: R^2 = (x - cx)^2 + (y - cy)^2 + (z - cz)^2
	// dot(p - c)
	// Do algebra a bit to find a, b, and c then use quadratic formula to find discriminant
	// Discriminant will determine whether there are 0, 1, or 2 solutions
	Vec3f oc(ray.origin - Center);
	float a = ray.dir.dot(ray.dir);
	float b = 2.0 * oc.dot(ray.dir);
	float c = oc.dot(oc) - Radius * Radius;
	float discriminant = b * b - 4 * a*c;
	if (discriminant > 0)
	{
		// Look for "-" first since it will be closer to camera
		float temp = (-b - sqrt(discriminant)) / (2.0f * a);
		if (temp < tMax && temp > tMin)
		{
			BuildHitRecord(rec, temp, ray);
			return true;
		}
		
		temp = (-b + sqrt(discriminant)) / (2.0f * a);
		if (temp < tMax && temp > tMin)
		{
			BuildHitRecord(rec, temp, ray);
			return true;
		}
	}

	return false;
}

void Sphere::BuildHitRecord(HitRecord_t& rec, float t, Rayf ray) const
{
	rec.t = t;
	rec.p = ray.GetPosOnRay(t);
	rec.normal = (rec.p - Center) / Radius;
}