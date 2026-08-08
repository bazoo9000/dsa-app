#pragma once

#include "Widget.h"

class ComboBox : public Widget
{
public:
	ComboBox(std::string id);
	ComboBox(std::string id, const std::vector<std::string>& items);
	~ComboBox();

protected:
	virtual inline void drawWidget() override;

public:
	void AddItem(std::string item);
	void RemoveItem(std::string item);
	std::string GetSelected() { return m_Items[m_Selected]; }
	int GetSelectedIndex() { return m_Selected; }
	void SetSelectedIndex(int index) { if (index > m_Items.size()) { index = m_Items.size() - 1; } m_Selected = index; }

private:
	std::string m_DrawId = "##"; // for imgui id
	std::vector<std::string> m_Items;
	int m_Selected;
};
