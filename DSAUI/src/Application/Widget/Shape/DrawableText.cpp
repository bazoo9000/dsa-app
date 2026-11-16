#include "../../../dsa_pch.h"

#include "DrawableText.h"

DrawableText::DrawableText(const std::string& text, ImFont* font, ImVec2 pos)
    : BasicText(text, font)
{
    m_Origin = pos;
}

void DrawableText::DrawShape(ImDrawList *drawList)
{
    drawList->AddText(m_Font, m_Font->LegacySize, GetFinalOriginPositon(), m_Color, m_Text.c_str(), m_Text.c_str() + m_Text.length());
}
