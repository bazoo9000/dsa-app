#include "../../dsa_pch.h"

#include "Widget.h"
#include "Logger/Logger.h"

void Widget::Draw()
{
	if (m_IsHidden)
	{
		return;
	}

	ImGui::BeginDisabled(m_IsDisabled);
	
	if (!m_AutoPos)
	{
		ImGui::SetCursorPos(m_Transform.position);
	}
	drawWidget();

	ImGui::EndDisabled();
}

void Widget::MoveTo(ImVec2 newPos)
{
	m_Transform.position = newPos;
}

void Widget::MoveBy(ImVec2 move)
{
	m_Transform.position.x += move.x;
	m_Transform.position.y += move.y;
}

void Widget::ScaleBy(float scale)
{
	if (scale < 0.0f)
	{
		LOG_GUI_ERROR("Failed to scale widget, used negative scale");
		return;
	}
	m_Transform.scale = { scale * m_Transform.scale.x, scale * m_Transform.scale.y };
}

void Widget::ScaleTo(ImVec2 newScale)
{
	m_Transform.scale = newScale;
}

void Widget::RotateBy(float degrees)
{
	m_Transform.rotation = degrees;
}
