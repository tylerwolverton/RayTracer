#pragma once

#include "Material.h"

class Metal : public Material
{
public:
	Metal(const Vec3f& a, float f)
		: albedo(a) 
	{
		fuzz = f < 1 ? f : 1;
	}

	virtual bool Scatter(const Rayf& ray, const HitRecord_t& rec, Vec3f& attentuation, Rayf& scattered) const
	{
		Vec3f rayDir = ray.dir;
		Vec3f reflected = reflect(rayDir.Normalize(), rec.normal);
		scattered = Rayf(rec.p, reflected + fuzz * GetRandomVectorInUnitSphere());
		attentuation = albedo;
		return scattered.dir.dot(rec.normal) > 0;
	}

	Vec3f albedo;
	float fuzz;

private:
	Vec3f reflect(const Vec3f& v, const Vec3f& n) const { return v - 2 * v.dot(n) * n; }
};