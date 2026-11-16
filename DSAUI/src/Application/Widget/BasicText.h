#pragma once

extern ImFont* FONT_DEFAULT;
extern ImFont* FONT_H1;
extern ImFont* FONT_H2;
extern ImFont* FONT_H3;
extern ImFont* FONT_H4;

class BasicText
{
public:
	BasicText() = default;
	BasicText(const std::string& text, ImFont* font = FONT_DEFAULT);
	virtual ~BasicText();

public:
	std::string GetText() { return m_Text; }
	void SetText(const std::string& newText) { m_Text = newText; }

public:
	static void LoadFonts(ImGuiIO& io, const std::string& fontName);
	static void ReloadFonts(ImGuiIO& io, const std::string& fontName);
	static void UnloadFonts(ImGuiIO& io);

protected:
	std::string m_Text;
	ImFont* m_Font = nullptr;
};