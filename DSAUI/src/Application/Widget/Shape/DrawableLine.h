#pragma once

#include "DrawableShape.h"
#include "Line.h"

class DrawableLine : public DrawableShape, public Line
{
public:
	DrawableLine(ImVec2 start, ImVec2 end, float thickness = 1.0f);
	virtual ~DrawableLine();

public:
	virtual void DrawShape(ImDrawList* drawList) override;
};