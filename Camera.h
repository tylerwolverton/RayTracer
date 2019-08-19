#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

#include "Ray.h"
#include "Misc.h"

class Camera 
{
public:
	// vup is the up vector for the view
	// vfov is top to bottom in degrees
	Camera(Vec3f lookFrom, Vec3f lookAt, Vec3f vup, float vfov, float aspect, float aperture, float focalLength)
		: m_origin(lookFrom),
		m_lensRadius(aperture / 2)
	{
		// Convert to radians
		float theta = vfov * M_PI / 180.0f;
		// Camera is centered on z axis so we need half height and width
		float halfHeight = tan(theta / 2.0f);
		float halfWidth = aspect * halfHeight;

		// Determine new basis for view
		m_frontVec = (lookFrom - lookAt).Normalize();
		m_rightVec = (vup.cross(m_frontVec)).Normalize();
		m_upVec = m_frontVec.cross(m_rightVec);
		m_upVec.y *= -1;

		m_lowerLeftCorner = m_origin - halfWidth * focalLength * m_rightVec - halfHeight * focalLength * m_upVec - focalLength * m_frontVec;
		m_horizontal = 2 * halfWidth * focalLength * m_rightVec;
		m_vertical = 2 * halfHeight * focalLength * m_upVec;
	}

	Rayf GetRay(float u, float v) 
	{
		Vec3f randomVec = m_lensRadius * GetRandomVectorInUnitDisc();
		Vec3f offset = m_rightVec * randomVec.x + m_upVec * randomVec.y;
		return Rayf(m_origin + offset, m_lowerLeftCorner + u * m_horizontal + v * m_vertical - m_origin - offset); 
	}

private:
	// Camera origin
	Vec3f m_origin;
	// Corner of box.
	Vec3f m_lowerLeftCorner;
	// Up and right vectors, dist from lower left corner to upper right
	Vec3f m_horizontal;
	Vec3f m_vertical;
	Vec3f m_rightVec, m_upVec, m_frontVec;
	float m_lensRadius;
};