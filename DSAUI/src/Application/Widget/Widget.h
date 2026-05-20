#pragma once

#include "../Transform.h"

// BIG TODO: Change all raw pointers to shared_ptr or create my own shared pointer so it can do internal logging
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
	Widget* GetParent() { return m_Parent; };
	void SetParent(Widget* parent) { m_Parent = parent; }
	void SetAutoPositioning(bool shouldAutoPos) { m_AutoPos = shouldAutoPos; }

protected:
	Transform m_Transform = { { 0.0f, 0.0f }, { 1.0f, 1.0f }, 0.0f }; // relative pos/scale/rot
	std::string m_Id; // for labeling/caching
	bool m_IsDisabled = false;
	bool m_IsHidden = false;
	Widget* m_Parent = nullptr; // for hierarchy
	bool m_AutoPos = false; // it positions the widget automatically using imgui default positioning
};