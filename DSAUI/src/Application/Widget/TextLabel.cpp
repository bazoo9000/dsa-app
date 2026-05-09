#include "../../dsa_pch.h"

#include "TextLabel.h"

TextLabel::TextLabel(std::string id, std::string text, ImFont* font)
{
	m_Id = id;
	m_Text = text;
	m_Font = font;
}

TextLabel::~TextLabel()
{
	// nimic
}

inline void TextLabel::drawWidget()
{
	ImGui::PushFont(m_Font);
	ImGui::Text(m_Text.c_str());
	ImGui::PopFont();
}
