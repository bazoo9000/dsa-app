#pragma once

#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(ImVec2 start, ImVec2 end);
	virtual ~Rectangle();

public:
	ImVec2 GetEnd() { return m_End; }
	void SetEnd(ImVec2 pMax) { m_End = pMax; }
	float GetWidth();
	float GetHeight();

protected:
	ImVec2 m_End;
};