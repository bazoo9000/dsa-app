#include "../../../dsa_pch.h"

#include "InteractableShape.h"
#include "Logger/Logger.h"

MouseAction InteractableShape::CheckMouseAction()
{
	ImGuiIO& io = ImGui::GetIO();

	bool isInside = IsInsideShape(io.MousePos);
	bool isClicked = io.MouseClicked[ImGuiMouseButton_Left];
	bool isHeld = io.MouseDown[ImGuiMouseButton_Left];
	bool isReleased = io.MouseReleased[ImGuiMouseButton_Left];

	// This is in case if holding and dragging accross
	// the screen even if not inside shape
	if (m_IsHeld && !isReleased)
	{
		return MouseAction::Hold;
	}

	if (isInside)
	{
		if (isClicked)
		{
			return MouseAction::Click;
		}
		if (isHeld)
		{
			m_IsHeld = true;
			return MouseAction::Hold;
		}
		if (isReleased)
		{
			m_IsHeld = false;
			return MouseAction::Release;
		}

		return MouseAction::Hover;
	}

	return MouseAction::None;
}

void InteractableShape::OnNothing()
{
	if (m_OnNothingCallback)
	{
		m_OnNothingCallback();
	}
}

void InteractableShape::OnHover()
{
	if (m_OnHoverCallback)
	{
		m_OnHoverCallback();
	}
	else
	{
		notImplemented("OnHover");
	}
}

void InteractableShape::OnClick()
{
	if (m_OnClickCallback)
	{
		m_OnClickCallback();
	}
	else
	{
		notImplemented("OnClick");
	}
}

void InteractableShape::OnHold()
{
	if (m_OnHoldCallback)
	{
		m_OnHoldCallback();
	}
	else
	{
		notImplemented("OnHold");
	}
}

void InteractableShape::OnRelease()
{
	if (m_OnReleaseCallback)
	{
		m_OnReleaseCallback();
	}
	else
	{
		notImplemented("OnRelease");
	}
}

void InteractableShape::notImplemented(std::string funcName)
{
	LOG_GUI_WARN((funcName + " is not implemented").c_str());
}
