#pragma once

#include "../../dsa_pch.h"

extern ImFont* FONT_DEFAULT;
extern ImFont* FONT_H1;
extern ImFont* FONT_H2;
extern ImFont* FONT_H3;
extern ImFont* FONT_H4;

void LoadFonts(ImGuiIO& io);

class BasicText
{
public:
	virtual ~BasicText() { m_Text.clear(); m_Font = nullptr; }

public:
	void ModifyText(std::string newText) { m_Text = newText; }

protected:
	std::string m_Text;
	ImFont* m_Font;
};