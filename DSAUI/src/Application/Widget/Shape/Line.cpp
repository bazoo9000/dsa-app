#include "../../../dsa_pch.h"

#include "Line.h"

Line::Line(ImVec2 start, ImVec2 end, float thickness)
	: m_End(end)
{
	m_Origin = start;
	m_Thickness = thickness;
}

Line::~Line()
{
}

void Line::DrawShape(ImDrawList* drawList, ImVec2 offset)
{
	drawList->AddLine(
		m_Origin + offset,
		m_End + offset,
		m_Color,
		m_Thickness
	);
}
