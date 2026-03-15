#pragma once

#include "Widget.h"

class RadioButton : public Widget
{
public:
	RadioButton(std::string id);
	RadioButton(std::string id, std::vector<std::string>& items);
	~RadioButton();

protected:
	virtual inline void drawWidget() override;

public:
	void AddItem(std::string item);
	void RemoveItem(std::string item);
	std::string GetSelected() { return m_Items[m_Selected]; }

private:
	std::vector<std::string> m_Items;
	int m_Selected;
};