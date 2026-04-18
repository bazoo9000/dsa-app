#pragma once

#include "Shape.h"

class Line : public Shape
{
public:
	Line(ImVec2 start, ImVec2 end);
	virtual ~Line() = default;

public:
	ImVec2 GetEnd() { return m_End; }
	void SetEnd(ImVec2 end) { m_End = end; }
	ImVec2 GetFinalEndPositon() { return m_GlobalOrigin + m_End; }

protected:
	// End position of the line
	ImVec2 m_End = { 0, 0 };
};