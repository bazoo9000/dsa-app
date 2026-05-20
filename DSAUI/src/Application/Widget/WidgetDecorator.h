#pragma once

#include "Widget.h"

// TODO: proxy the modifications to the decorated widget
class WidgetDecorator : public Widget
{
public:
	WidgetDecorator(Widget* widget);
	~WidgetDecorator() = default;

public:
	Widget* GetWidget() { return m_Widget; }
	void SetWidget(Widget* widget) { putWidget(widget); }

protected:
	void putWidget(Widget* widget);

protected:
	Widget* m_Widget; // decorated widget
};