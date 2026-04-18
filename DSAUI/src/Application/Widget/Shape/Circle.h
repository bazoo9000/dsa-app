#pragma once

#include "Shape.h"

class Circle : public Shape
{
public:
	Circle(ImVec2 center, float radius);
	virtual ~Circle();

public:
	float GetRadius() { return m_Radius; }
	void SetRadius(float radius) { m_Radius = radius; }

protected:
	float m_Radius;
};