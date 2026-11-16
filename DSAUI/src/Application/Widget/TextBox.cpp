#include "../../dsa_pch.h"

#include "TextBox.h"

TextBox::TextBox(const std::string& id, const std::string& text, ImFont* font)
	: BasicText(text, font)
{
	m_Id = id;
}

TextBox::~TextBox()
{
	// nimic
}

inline void TextBox::drawWidget()
{
    ImGui::PushTextWrapPos( m_Transform.scale.x);
	ImGui::PushFont(m_Font);
	ImGui::Text(m_Text.c_str());
	ImGui::PopFont();
	ImGui::PopTextWrapPos();
}
