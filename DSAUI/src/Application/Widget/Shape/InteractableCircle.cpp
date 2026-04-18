#include "../../../dsa_pch.h"

#include "InteractableCircle.h"

InteractableCircle::InteractableCircle(ImVec2 center, float radius, float thickness)
	: DrawableCircle(center, radius, thickness)
{
}

void InteractableCircle::DrawShape(ImDrawList* drawList)
{
	// Check for events here

	DrawableCircle::DrawShape(drawList);
}

bool InteractableCircle::IsInsideShape(ImVec2 point)
{
	ImVec2 finalPos = m_GlobalOrigin + m_Origin;
	float dx = (point.x - finalPos.x) * (point.x - finalPos.x);
	float dy = (point.y - finalPos.y) * (point.y - finalPos.y);
	float rhs = dx + dy;
	float lhs = m_Radius * m_Radius;

	return rhs <= lhs;
}
