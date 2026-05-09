#include "../../dsa_pch.h"

#include "Button.h"

#include "Logger/Logger.h"

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
	if (ImGui::Button(m_Label.c_str(), m_Transform.scale))
	{
		if (m_Callback)
		{
			m_Callback();
		}
		else
		{
			LOG_GUI_WARN("Button %s has no function", m_Id.c_str());
		}
	}
}
