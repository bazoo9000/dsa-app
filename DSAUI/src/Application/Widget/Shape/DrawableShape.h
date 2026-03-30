#pragma once

#include "imgui.h"

class DrawableShape
{
public:
	DrawableShape() = default;
	virtual ~DrawableShape() = default;

public:
	virtual void DrawShape(ImDrawList* drawList, ImVec2 offset = { 0, 0 }) = 0;

public:
	ImVec2 GetOrigin() { return m_Origin; }
	void SetOrigin(ImVec2 origin) { m_Origin = origin; }
	ImU32 GetColor() { return m_Color; }
	void SetColor(ImU32 color) { m_Color = color; }
	float GetThickness() { return m_Thickness; }
	void SetThickness(float thickness) { m_Thickness = thickness; }

protected:
	ImU32 m_Color = IM_COL32_BLACK;
	ImVec2 m_Origin = { 0, 0 };
	float m_Thickness = 1.0f;
};