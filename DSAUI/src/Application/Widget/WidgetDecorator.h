#pragma once

#include "Widget.h"

// TODO: proxy the modifications to the decorated widget
class WidgetDecorator : public Widget
{
public:
	WidgetDecorator(Widget* widget);
	~WidgetDecorator() = default;

public:
	Widget* GetWidgetComponent() { return m_WidgetComponent; }
	void SetWidgetComponent(Widget* widget) { putWidget(widget); }

protected:
	void putWidget(Widget* widget);

protected:
	Widget* m_WidgetComponent; // decorated widget
};