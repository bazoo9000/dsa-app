#include "../../../dsa_pch.h"

#include "DrawableLine.h"

DrawableLine::DrawableLine(ImVec2 start, ImVec2 end, float thickness)
	: Line(start, end)
{
	m_Thickness = thickness;
}

DrawableLine::~DrawableLine()
{
}

void DrawableLine::DrawShape(ImDrawList* drawList)
{
	ImVec2 start = m_GlobalOrigin + m_Origin;
	ImVec2 end = m_GlobalOrigin + m_End;

	drawList->AddLine(
		start,
		end,
		m_Color,
		m_Thickness
	);
}
