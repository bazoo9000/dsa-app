#include "../../dsa_pch.h"

#include "CustomWidget.h"

#include "Logger/Logger.h"

CustomWidget::CustomWidget(std::string id)
{
	m_Id = id;
}

CustomWidget::~CustomWidget()
{
}

inline void CustomWidget::drawWidget()
{
	if (m_CustomScript)
	{
		m_CustomScript();
	}
	else
	{
		LOG_GUI_WARN("Custom script wasn't applied to %s", m_Id.c_str());
	}
}
