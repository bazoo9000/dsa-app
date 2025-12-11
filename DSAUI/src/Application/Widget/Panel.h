#pragma once

#include "../../dsa_pch.h"
#include "Widget.h"

class Panel : public Widget
{
public:
	Panel(std::string id);
	Panel(std::string id, std::vector<Widget*>& widgets);
	~Panel();

public:
	virtual inline void Draw() override;

public:
	void AddWidget(Widget* widget);
	void RemoveWidget(std::string id);

private:
	 std::vector<Widget*> m_Children; // Panel only
};