#pragma once
#include "Hitable.h"

class Sphere : public Hitable
{
public:
	Vec3f Center;
	float Radius;

	Sphere(Vec3f center, float radius)
		: Center(center),
		Radius(radius)
	{}

	bool Hit(const Rayf& ray, float tMin, float tMax, HitRecord_t& rec) const override;

private:
	void BuildHitRecord(HitRecord_t& rec, float t, Rayf ray) const;
};