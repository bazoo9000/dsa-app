#pragma once

#include "DrawableShape.h"
#include "Circle.h"

class DrawableCircle : public DrawableShape, public Circle
{
public:
	DrawableCircle(ImVec2 center, float radius, float thickness = 1.0f);
	virtual ~DrawableCircle();

public:
	virtual void DrawShape(ImDrawList* drawList) override;
};