#pragma once

#include "InteractableShape.h"
#include "DrawableCircle.h"

class InteractableCircle : public InteractableShape, public DrawableCircle
{
public:
	InteractableCircle(ImVec2 center, float radius, float thickness = 1.0f);
	virtual ~InteractableCircle() = default;

public:
	virtual void DrawShape(ImDrawList* drawList) override;

protected:
	virtual bool isInsideShape(ImVec2 point) override;
};
