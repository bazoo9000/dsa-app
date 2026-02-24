#pragma once

#include "../Transform.h"

class Widget
{
public:
	Widget() = default;
	virtual ~Widget() = default;

public:
	virtual inline void Draw() = 0;

public:
	void MoveTo(ImVec2 newPos);
	void MoveBy(ImVec2 move);
	void ScaleBy(float scale);
	void ScaleTo(ImVec2 newScale);
	void RotateBy(float degrees);

public:
	std::string GetId() { return m_Id; }

protected:
	Transform m_Transform = { { 0.0f, 0.0f }, { 1.0f, 1.0f }, 0.0f }; // relative pos/scale/rot
	std::string m_Id; // for labeling/caching
};