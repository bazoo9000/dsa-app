#include "../../dsa_pch.h"

#include "BasicText.h"

ImFont* FONT_DEFAULT = nullptr;
ImFont* FONT_H1 = nullptr;
ImFont* FONT_H2 = nullptr;
ImFont* FONT_H3 = nullptr;
ImFont* FONT_H4 = nullptr;

void LoadFonts(ImGuiIO& io)
{
	FONT_DEFAULT = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Medium.ttf", 16.0f);
	FONT_H1 = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Medium.ttf", 48.0f);
	FONT_H2 = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Medium.ttf", 40.0f);
	FONT_H3 = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Medium.ttf", 32.0f);
	FONT_H4 = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Medium.ttf", 24.0f);
}