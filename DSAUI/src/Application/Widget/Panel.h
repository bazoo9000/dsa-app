#pragma once

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
	// TODO: add an interface for having the power to do hierarhical rendering
	void AddWidget(Widget* widget);
	Widget* GetWidget(std::string id);
	void RemoveWidget(std::string id);

private:
	// TODO: instead of vector, use hashmap ffs
	std::vector<Widget*> m_Children; // Panel only
};