#pragma once
#include "Ray.h"

struct HitRecord_t {
	float t;
	Vec3f p;
	Vec3f normal;
};

class Hitable {
public:
	virtual ~Hitable() {}
	virtual bool Hit(const Rayf& ray, float tMin, float tMax, HitRecord_t& rec) const = 0;
};
