#pragma once
#include "Vec3.h";

template<class T>
class Ray 
{
public:
	Vec3<T> origin;
	Vec3<T> dir;

	Ray(const Vec3<T>& p_origin, const Vec3<T>& p_dir)
		: origin(p_origin),
		dir(p_dir)
	{}

	inline T GetPosOnRay(float t) { return origin + t * dir; }
};

typedef Ray<float> Rayf;
typedef Ray<int> Rayi;