#pragma once

#include "Rectangle.h"
#include "DrawableShape.h"

class DrawableRectangle : public DrawableShape, public Rectangle
{
public:
	DrawableRectangle(ImVec2 start, ImVec2 end);
	virtual ~DrawableRectangle();

public:
	virtual void DrawShape(ImDrawList* drawList) override;

public:
	float GetRounding() { return m_Rounding; }
	void SetRounding(float rounding) { m_Rounding = rounding; }

private:
	float m_Rounding = 0.0f;
};