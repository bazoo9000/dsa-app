#pragma once

#include "Widget.h"

class Panel : public Widget
{
public:
	Panel(std::string id);
	Panel(std::string id, std::vector<Widget*>& widgets);
	~Panel();

protected:
	virtual inline void drawWidget() override;

public:
	// TODO: add an interface for having the power to do hierarhical rendering
	void AddWidget(Widget* widget);
	Widget* GetWidget(std::string id);
	void RemoveWidget(std::string id);
	// TODO: maybe add a flag builder, but i dont think its necessary now to do it
	void ShowBorder() { m_ChildFlags |= ImGuiChildFlags_Borders; }
	void HideBorder() { m_ChildFlags &= (~ImGuiChildFlags_Borders); }
	void ShowScrollBar() { m_WindowFlags &= (~ImGuiWindowFlags_NoScrollbar); m_WindowFlags &= (~ImGuiWindowFlags_NoScrollWithMouse);}
	void HideScrollBar() { m_WindowFlags |= ImGuiWindowFlags_NoScrollbar; m_WindowFlags |= ImGuiWindowFlags_NoScrollWithMouse; }

private:
	void addChild(std::string id, Widget* widget);

private:
	std::unordered_map<std::string, Widget*> m_Children; // Panel only
	std::string m_DrawId = "##"; // for imgui id
	ImGuiChildFlags m_ChildFlags = ImGuiChildFlags_Borders;
	ImGuiChildFlags m_WindowFlags = ImGuiWindowFlags_NoResize;
};