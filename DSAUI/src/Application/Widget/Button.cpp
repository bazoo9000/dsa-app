#include "Button.h"

Button::Button(std::string id, std::string label)
{
	m_Id = "##" + id;
	m_Label = label;
}

Button::~Button()
{
}

void Button::Draw()
{
	ImGui::SetCursorPos(m_Transform.position);
	//ImGui::BeginChild(m_Id.c_str());
	if (ImGui::Button(m_Label.c_str(), m_Transform.scale))
	{
		m_Callback();
	}
	//ImGui::EndChild();
}
