#pragma once

#include "DrawableShape.h"

class Line : public DrawableShape
{
public:
	Line(ImVec2 start, ImVec2 end, float thickness = 1.0f);
	virtual ~Line();

public:
	virtual void DrawShape(ImDrawList* drawList, ImVec2 offset = { 0, 0 }) override;

public:
	ImVec2 GetEnd() { return m_End; }
	void GetEnd(ImVec2 end) { m_End = end; }

private:
	ImVec2 m_End;
};