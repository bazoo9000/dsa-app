#include "TextBox.h"

TextBox::TextBox(std::string id, std::string text)
	: m_Text(text)
{
	m_Id = "##" + id;
}

TextBox::~TextBox()
{
	m_Text.clear();
}

inline void TextBox::Draw()
{
	ImGui::SetCursorPos(m_Transform.position);
    ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + m_Transform.scale.x);
	ImGui::Text(m_Text.c_str());
    ImGui::PopTextWrapPos();
}
