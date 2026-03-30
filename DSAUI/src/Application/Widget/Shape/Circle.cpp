#include "../../../dsa_pch.h"

#include "Circle.h"

Circle::Circle(ImVec2 center, float radius, float thickness)
	: m_Radius(radius)
{
	m_Origin = center;
	m_Thickness = thickness;
}

Circle::~Circle()
{
}

void Circle::DrawShape(ImDrawList* drawList, ImVec2 offset)
{
	drawList->AddCircle(
		m_Origin + offset,
		m_Radius,
		m_Color,
		0,
		m_Thickness
	);
}