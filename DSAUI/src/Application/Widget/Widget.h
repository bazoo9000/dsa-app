#pragma once

#include "../Transform.h"

class Widget
{
public:
	Widget() = default;
	virtual ~Widget() = default;

public:
	void Draw();
	void Enable() { m_IsDisabled = false; }
	void Disable() { m_IsDisabled = true; }
	void Show() { m_IsHidden = false; }
	void Hide() { m_IsHidden = true; }

protected:
	virtual inline void drawWidget() = 0;

public:
	void MoveTo(ImVec2 newPos);
	void MoveBy(ImVec2 move);
	void ScaleBy(float scale);
	void ScaleTo(ImVec2 newScale);
	void RotateBy(float degrees);

public:
	std::string GetId() { return m_Id; }
	Transform GetTransform() { return m_Transform; }

protected:
	Transform m_Transform = { { 0.0f, 0.0f }, { 1.0f, 1.0f }, 0.0f }; // relative pos/scale/rot
	std::string m_Id; // for labeling/caching
	bool m_IsDisabled = false;
	bool m_IsHidden = false;
};