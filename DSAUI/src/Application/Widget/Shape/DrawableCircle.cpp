#include "../../../dsa_pch.h"

#include "DrawableCircle.h"

DrawableCircle::DrawableCircle(ImVec2 center, float radius, float thickness)
	: Circle(center, radius)
{
	m_Thickness = thickness;
}

DrawableCircle::~DrawableCircle()
{
}

void DrawableCircle::DrawShape(ImDrawList* drawList)
{
	ImVec2 finalPos = m_GlobalOrigin + m_Origin;
	
	if (!m_Filled)
	{
		drawList->AddCircle(
			finalPos,
			m_Radius,
			m_Color,
			0,
			m_Thickness
		);
	}
	else
	{
		drawList->AddCircleFilled(
			finalPos,
			m_Radius,
			m_Color
		);
	}
}