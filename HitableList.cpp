#include "HitableList.h"

HitableList::~HitableList()
{
	for (int i = 0; i < m_hitList.size(); i++)
	{
		delete(m_hitList[i]);
	}
	
	m_hitList.clear();
}

bool HitableList::Hit(const Rayf& ray, float tMin, float tMax, HitRecord_t& rec) const
{
	bool hitAnything = false;
	float closestSoFar = tMax;
	for (auto& obj : m_hitList)
	{
		// Only check for hits that are closer than we already have to grab the frontmost object
		if (obj->Hit(ray, tMin, closestSoFar, rec))
		{
			hitAnything = true;
			closestSoFar = rec.t;
		}
	}

	return hitAnything;
}
