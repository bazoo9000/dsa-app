#pragma once

#include "DrawableShape.h"

class Circle : public DrawableShape
{
public:
	Circle(ImVec2 center, float radius, float thickness = 1.0f);
	virtual ~Circle();

public:
	virtual void DrawShape(ImDrawList* drawList, ImVec2 offset = { 0, 0 }) override;

public:
	float GetRadius() { return m_Radius; }
	void SetRadius(float radius) { m_Radius = radius; }

private:
	float m_Radius;
};