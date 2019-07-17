#pragma once
#include "Material.h"
#include "Misc.h"

class Lambertian : public Material
{
public:
	Lambertian(const Vec3f& a)
		: albedo(a) {}

	virtual bool Scatter(const Rayf& ray, const HitRecord_t& rec, Vec3f& attentuation, Rayf& scattered) const
	{
		Vec3f target = rec.p + rec.normal + GetRandomVectorInUnitSphere();
		scattered = Rayf(rec.p, target - rec.p);
		attentuation = albedo;
		return true;
	}

	Vec3f albedo;
};
