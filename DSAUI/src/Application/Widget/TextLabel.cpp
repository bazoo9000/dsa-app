#include "TextLabel.h"

TextLabel::TextLabel(std::string id, std::string text)
	: m_Text(text)
{
	m_Id = "##" + id;
}

TextLabel::~TextLabel()
{
	m_Text.clear();
}

inline void TextLabel::Draw()
{
	ImGui::SetCursorPos(m_Transform.position);
	ImGui::Text(m_Text.c_str());
}
