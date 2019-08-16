#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

#include "Ray.h"

class Camera 
{
public:
	// vup is the up vector for the view
	// vfov is top to bottom in degrees
	Camera(Vec3f lookFrom, Vec3f lookAt, Vec3f vup, float vfov, float aspect)
		: m_origin(lookFrom)
	{
		// Convert to radians
		float theta = vfov * M_PI / 180.0f;
		// Camera is centered on z axis so we need half height and width
		float halfHeight = tan(theta / 2.0f);
		float halfWidth = aspect * halfHeight;

		// Determine new basis for view
		Vec3f w = (lookFrom - lookAt).Normalize();
		Vec3f u = (vup.cross(w)).Normalize();
		Vec3f v = (w.cross(u));
		v.y *= -1;
		//u.x *= -1;

		m_lowerLeftCorner = m_origin - halfWidth * u - halfHeight * v - w;
		m_horizontal = 2 * halfWidth * u;
		m_vertical = 2 * halfHeight * v;
	}

	Rayf GetRay(float u, float v) { return Rayf(m_origin, m_lowerLeftCorner + u * m_horizontal + v * m_vertical - m_origin); }

private:
	// Camera origin
	Vec3f m_origin;
	// Corner of box.
	Vec3f m_lowerLeftCorner;
	// Up and right vectors, dist from lower left corner to upper right
	Vec3f m_horizontal;
	Vec3f m_vertical;
};