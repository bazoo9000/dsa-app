#pragma once

#include "imgui.h"

enum class MouseAction
{
	None = 0,
	Hover,
	Click,
	Hold,
	Release
};

class InteractableShape
{
public:
	virtual ~InteractableShape() = default;

public:
	virtual bool IsInsideShape(ImVec2 point) = 0; // TODO: make it protected
	MouseAction CheckMouseAction();

	void OnNothing();
	void OnHover();
	void OnClick();
	void OnHold();
	void OnRelease();

	void SetOnNothingCallback(std::function<void()> callback) { m_OnNothingCallback = callback; }
	void SetOnHoverCallback(std::function<void()> callback)   { m_OnHoverCallback = callback; }
	void SetOnClickCallback(std::function<void()> callback)   { m_OnClickCallback = callback; }
	void SetOnHoldCallback(std::function<void()> callback)    { m_OnHoldCallback = callback; }
	void SetOnReleaseCallback(std::function<void()> callback) { m_OnReleaseCallback = callback; }

protected:
	void notImplemented(std::string funcName);

protected:
	std::function<void()> m_OnNothingCallback;
	std::function<void()> m_OnHoverCallback;
	std::function<void()> m_OnClickCallback;
	std::function<void()> m_OnHoldCallback;
	std::function<void()> m_OnReleaseCallback;
};