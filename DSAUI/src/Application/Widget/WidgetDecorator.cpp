#include "../../dsa_pch.h"

#include "WidgetDecorator.h"

#include "Logger/Logger.h"

WidgetDecorator::WidgetDecorator(Widget* widget)
{
	putWidget(widget);
}

void WidgetDecorator::putWidget(Widget* widget)
{
	if (widget == nullptr)
	{
		LOG_GUI_WARN("Widget decorator can't decorate a null widget");
		m_Id = "";
	}
	else
	{
		// TODO: think if this is good idea, when searching for widget this will work fine but modifying will be not so good
		m_Id = widget->GetId();
	}

	m_WidgetComponent = widget;
}
