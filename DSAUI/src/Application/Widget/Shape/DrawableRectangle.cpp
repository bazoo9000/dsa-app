#include "../../../dsa_pch.h"

#include "DrawableRectangle.h"

DrawableRectangle::DrawableRectangle(ImVec2 start, ImVec2 end)
	: Rectangle(start, end)
{
}

DrawableRectangle::~DrawableRectangle()
{
}

void DrawableRectangle::DrawShape(ImDrawList* drawList)
{
	ImVec2 start = m_GlobalOrigin + m_Origin;
	ImVec2 end = m_GlobalOrigin + m_End;

	if (!m_Filled)
	{
		drawList->AddRect(
			start,
			end,
			m_Color,
			m_Rounding,
			0,
			m_Thickness
		);
	}
	else
	{
		drawList->AddRectFilled(
			start,
			end,
			m_Color,
			m_Rounding
		);
	}
}
