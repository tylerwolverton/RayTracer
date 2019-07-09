#pragma once

#include "Ray.h"

class Camera 
{
public:
	Camera()
		: m_origin(Vec3f(0, 0, 0)),
		m_lowerLeftCorner(Vec3f(-2, -1, -1)),
		m_horizontal(Vec3f(4, 0, 0)),
		m_vertical(Vec3f(0, 2, 0))
	{}

	Rayf GetRay(float u, float v) { return Rayf(m_origin, m_lowerLeftCorner + u * m_horizontal + v * m_vertical); }

private:
	// Camera origin
	Vec3f m_origin;
	// Corner of box.
	Vec3f m_lowerLeftCorner;
	// Up and right vectors, dist from lower left corner to upper right since box is 
	// (-2,  1, -1) ----------- (2,  1, -1)
	// |                                  |
	// (-2, -1, -1) ----------- (2, -1, -1)
	Vec3f m_horizontal;
	Vec3f m_vertical;
};