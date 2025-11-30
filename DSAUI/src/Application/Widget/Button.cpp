#include "Button.h"

Button::Button(std::string label)
{
	m_Id = "##" + label;
	m_Label = label;
}

Button::~Button()
{
}

void Button::Draw()
{
	ImGui::BeginChild(m_Id.c_str());
	//if (ImGui::Button(m_Label.c_str(), m_Transform.scale))
	if (ImGui::Button(m_Label.c_str()))
	{
		m_Callback();
	}
	ImGui::EndChild();
}
