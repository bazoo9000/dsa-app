#include "../../dsa_pch.h"

#include "BasicText.h"

ImFont* FONT_DEFAULT = nullptr;
ImFont* FONT_H1 = nullptr;
ImFont* FONT_H2 = nullptr;
ImFont* FONT_H3 = nullptr;
ImFont* FONT_H4 = nullptr;

BasicText::BasicText(const std::string& text, ImFont* font)
{
	m_Text = text;
	m_Font = font;
}

BasicText::~BasicText()
{
	m_Text.clear();
	m_Font = nullptr;
}

void BasicText::LoadFonts(ImGuiIO& io, const std::string& fontName)
{
	std::string fontPath = "fonts/" + fontName + ".ttf";

	FONT_DEFAULT = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 16.0f);
	FONT_H1 = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 48.0f);
	FONT_H2 = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 40.0f);
	FONT_H3 = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 32.0f);
	FONT_H4 = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 24.0f);
}

void BasicText::ReloadFonts(ImGuiIO& io, const std::string& fontName)
{
	UnloadFonts(io);
	LoadFonts(io, fontName);
}

void BasicText::UnloadFonts(ImGuiIO& io)
{
	io.Fonts->RemoveFont(FONT_DEFAULT);
	io.Fonts->RemoveFont(FONT_H1);
	io.Fonts->RemoveFont(FONT_H2);
	io.Fonts->RemoveFont(FONT_H3);
	io.Fonts->RemoveFont(FONT_H4);
}