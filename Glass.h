#pragma once
#include <math.h>

#include "Material.h"

class Glass : public Material
{
public:
	Glass(float nr)
		: nRatio(nr)
	{}

	virtual bool Scatter(const Rayf& ray, const HitRecord_t& rec, Vec3f& attentuation, Rayf& scattered) const
	{
		Vec3f outwardNormal;
		Vec3f reflected = reflect(ray.dir, rec.normal);
		float ni_over_nt;
		attentuation = Vec3f(1, 1, 1);
		Vec3f refracted;
		float reflectProb;
		float cosine;
		
		float RDotN = ray.dir.dot(rec.normal);
		if (RDotN > 0)
		{
			outwardNormal = -rec.normal;
			ni_over_nt = nRatio;
			cosine = nRatio * RDotN / ray.dir.GetMagnitude();
		}
		else
		{
			outwardNormal = rec.normal;
			ni_over_nt = 1 / nRatio;
			cosine = - RDotN / ray.dir.GetMagnitude();
		}

		if (refract(ray.dir, outwardNormal, ni_over_nt, refracted))
		{
			reflectProb = schlick(cosine, nRatio);
		}
		else
		{
			scattered = Rayf(rec.p, reflected);
			reflectProb = 1.0f;
		}

		if (randf01() < reflectProb)
		{
			scattered = Rayf(rec.p, reflected);
		}
		else
		{
			scattered = Rayf(rec.p, refracted);
		}
		return true;
	}

	float nRatio;

private:
	Vec3f reflect(const Vec3f& v, const Vec3f& n) const { return v - 2 * v.dot(n) * n; }

	// ni_over_nt is the refraction indices of each material
	bool refract(Vec3f v, const Vec3f& n, float ni_over_nt, Vec3f& refracted) const
	{
		v.Normalize();
		float dt = v.dot(n);
		float discriminant = 1 - ni_over_nt*ni_over_nt * (1 - dt*dt);
		
		if (discriminant > 0)
		{
			refracted = ni_over_nt * (v - n * dt) - n * sqrt(discriminant);
			return true;
		}

		return false;
	}

	float schlick(float cosine, float nRatio) const
	{
		float r0 = (1 - nRatio) / (1 + nRatio);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};