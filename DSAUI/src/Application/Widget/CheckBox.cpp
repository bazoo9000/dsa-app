#include "../../dsa_pch.h"

#include "CheckBox.h"

CheckBox::CheckBox(std::string id, std::string label, bool initialVal)
	: m_Label(label), m_Value(initialVal)
{
	m_Id = id;
}

CheckBox::~CheckBox()
{
}

inline void CheckBox::drawWidget()
{
	ImGui::SetCursorPos(m_Transform.position);
	ImGui::Checkbox(m_Label.c_str(), &m_Value);
}
