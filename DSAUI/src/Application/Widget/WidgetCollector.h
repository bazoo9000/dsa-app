#pragma once

#include "Widget.h"

class WidgetCollector : public Widget
{
public:
	virtual ~WidgetCollector() = default;

public:
	void AddWidget(Widget* widget);
	Widget* GetWidget(std::string id);
	void RemoveWidget(std::string id);

protected:
	void addChild(std::string id, Widget* widget);

private:
	Widget* tryFindCollector(Widget* widget, std::string id);
	Widget* tryFindDecorator(Widget* widget, std::string id);

protected:
	std::unordered_map<std::string, std::list<Widget*>::iterator> m_ChildrenMap; // for fast search
	std::list<Widget*> m_ChildrenList; // for ordering
};