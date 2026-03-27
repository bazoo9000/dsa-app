#include "../../../dsa_pch.h"

#include "Circle.h"

Circle::Circle(ImVec2 center, float radius)
	: m_Radius(radius)
{
	m_Origin = center;
}

Circle::~Circle()
{
}

void Circle::DrawShape(ImDrawList* drawList, ImVec2 offset)
{
	drawList->AddCircleFilled(
		m_Origin + offset,
		m_Radius,
		m_Color
	);
}