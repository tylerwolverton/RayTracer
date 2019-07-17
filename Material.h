#pragma once
#include "Ray.h"
#include "Hitable.h"

class Material
{
public:
	virtual bool Scatter(const Rayf& ray, const HitRecord_t& rec, Vec3f& attentuation, Rayf& scattered) const = 0;
};