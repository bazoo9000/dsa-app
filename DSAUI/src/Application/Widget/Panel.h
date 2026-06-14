#pragma once

#include "WidgetCollector.h"

class Panel : public WidgetCollector
{
public:
	Panel(std::string id);
	Panel(std::string id, std::vector<Widget*>& widgets);
	~Panel();

protected:
	virtual inline void drawWidget() override;

public:
	// TODO: maybe add a flag builder, but i dont think its necessary now to do it
	void ShowBorder() { m_ChildFlags |= ImGuiChildFlags_Borders; }
	void HideBorder() { m_ChildFlags &= (~ImGuiChildFlags_Borders); }
	void ShowScrollBar() { m_WindowFlags &= (~ImGuiWindowFlags_NoScrollbar); m_WindowFlags &= (~ImGuiWindowFlags_NoScrollWithMouse);}
	void HideScrollBar() { m_WindowFlags |= ImGuiWindowFlags_NoScrollbar; m_WindowFlags |= ImGuiWindowFlags_NoScrollWithMouse; }

private:
	std::string m_DrawId = "##"; // for imgui id
	ImGuiChildFlags m_ChildFlags = ImGuiChildFlags_Borders;
	ImGuiChildFlags m_WindowFlags = ImGuiWindowFlags_NoResize;
};