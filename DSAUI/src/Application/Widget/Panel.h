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
	void ShowBorder() { m_Flags |= ImGuiChildFlags_Borders; }
	void HideBorder() { m_Flags &= (~ImGuiChildFlags_Borders); }

private:
	void addChild(std::string id, Widget* widget);

private:
	std::unordered_map<std::string, Widget*> m_Children; // Panel only
	std::string m_DrawId = "##"; // for imgui id
	ImGuiChildFlags m_Flags = ImGuiChildFlags_Borders;
};