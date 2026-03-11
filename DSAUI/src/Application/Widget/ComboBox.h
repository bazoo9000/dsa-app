#pragma once

#include "Widget.h"

class ComboBox : public Widget
{
public:
	ComboBox(std::string id);
	ComboBox(std::string id, std::vector<std::string>& items);
	~ComboBox();

public:
	virtual inline void Draw() override;

public:
	void AddItem(std::string item);
	void RemoveItem(std::string item);
	std::string GetSelected() { return m_Items[m_Selected]; }

private:
	std::string m_DrawId = "##"; // for imgui id
	std::vector<std::string> m_Items;
	int m_Selected;
};