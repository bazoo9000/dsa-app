#include "../../dsa_pch.h"

#include "Button.h"

Button::Button(std::string id, std::string label)
{
	m_Id = id;
	m_Label = label;
}

Button::~Button()
{
}

inline void Button::drawWidget()
{
	ImGui::SetCursorPos(m_Transform.position);
	if (ImGui::Button(m_Label.c_str(), m_Transform.scale))
	{
		m_Callback();
	}
}
