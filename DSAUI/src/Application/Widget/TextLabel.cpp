#include "../../dsa_pch.h"

#include "TextLabel.h"

TextLabel::TextLabel(const std::string& id, const std::string& text, ImFont* font)
	: BasicText(text, font)
{
	m_Id = id;
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
