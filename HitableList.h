#pragma once
#include "Hitable.h"
#include <vector>

class HitableList : public Hitable
{
public:
	HitableList(std::vector<Hitable*> l, int n)
	: m_hitList(l),
	m_hitListLength(n)
	{}
	
	virtual ~HitableList() override;

	bool Hit(const Rayf& ray, float tMin, float tMax, HitRecord_t& rec) const override;

private:
	std::vector<Hitable*> m_hitList;
	int m_hitListLength;
};

