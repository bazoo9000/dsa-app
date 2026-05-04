#pragma once

#include "Widget.h"

class Tab : public Widget
{
private:
	struct TabData
	{
		Widget* widget = nullptr;
		bool selected = false;
		std::string name = "";

		TabData(Widget* w = nullptr, bool sel = false, std::string name = "")
			: widget(w), selected(sel), name(name)
		{
		}
	};

public:
	Tab(std::string id);
	Tab(std::string id, std::vector<Widget*>& widgets);
	~Tab();

protected:
	virtual inline void drawWidget() override;

public:
	void AddTabItem(Widget* widget, std::string name, bool selected = false);
	Widget* GetTabItemWidget(std::string id);
	bool GetTabItemSelected(std::string id);
	void SetTabItemSelected(std::string id, bool selected);
	std::string GetTabItemName(std::string id);
	void RemoveTabItem(std::string id);
	std::vector<std::string> GetAllKeys(); // TODO: now i really need to interface this

private:
	void addItem(std::string id, TabData data);

private:
	std::unordered_map<std::string, TabData> m_TabItems;
	std::string m_DrawId = "##"; // for imgui id

};