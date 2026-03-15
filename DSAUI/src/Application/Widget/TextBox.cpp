#include "../../dsa_pch.h"

#include "TextBox.h"

TextBox::TextBox(std::string id, std::string text, ImFont* font)
{
	m_Id = id;
	m_Text = text;
	m_Font = font;
}

TextBox::~TextBox()
{
	// nimic
}

inline void TextBox::drawWidget()
{
	ImGui::SetCursorPos(m_Transform.position);
    ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + m_Transform.scale.x);
	ImGui::PushFont(m_Font);
	ImGui::Text(m_Text.c_str());
	ImGui::PopFont();
	ImGui::PopTextWrapPos();
}
