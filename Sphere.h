#pragma once
#include "Hitable.h"
#include "Material.h"

class Sphere : public Hitable
{
public:
	Vec3f Center;
	float Radius;
	Material* Mat;

	Sphere(Vec3f center, float radius, Material* mat)
		: Center(center),
		Radius(radius),
		Mat(mat)
	{}

	~Sphere();

	bool Hit(const Rayf& ray, float tMin, float tMax, HitRecord_t& rec) const override;

private:
	void BuildHitRecord(HitRecord_t& rec, float t, Rayf ray) const;
};