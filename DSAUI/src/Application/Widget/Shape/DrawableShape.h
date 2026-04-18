#pragma once

#include "imgui.h"

class DrawableShape
{
public:
	virtual ~DrawableShape() = default;

public:
	virtual void DrawShape(ImDrawList* drawList) = 0;

public:
	ImU32 GetColor() { return m_Color; }
	void SetColor(ImU32 color) { m_Color = color; }
	float GetThickness() { return m_Thickness; }
	void SetThickness(float thickness) { m_Thickness = thickness; }
	float GetFilled() { return m_Filled; }
	void SetFilled(bool filled) { m_Filled = filled; }

protected:
	// Shape color, +get/+set
	ImU32 m_Color = IM_COL32_BLACK;
	// Thickness of shape line(s), +get/+set
	float m_Thickness = 1.0f;
	// If shape can be filled or not, TODO: move this since line is a shape that cant be filled
	bool m_Filled = false;
};