#include "../../dsa_pch.h"

#include "Tooltip.h"

Tooltip::Tooltip(Widget* widget, std::string text)
	: WidgetDecorator(widget)
{
	m_Text = text;
	m_DelayFlag = ImGuiHoveredFlags_DelayNormal;
}

void Tooltip::SetDelay(TooltipDelay delay)
{
	switch (delay)
	{
	case TooltipDelay::None:   m_DelayFlag = ImGuiHoveredFlags_DelayNone;   break;
	case TooltipDelay::Short:  m_DelayFlag = ImGuiHoveredFlags_DelayShort;  break;
	case TooltipDelay::Normal: m_DelayFlag = ImGuiHoveredFlags_DelayNormal; break;
	}
}

inline void Tooltip::drawWidget()
{
	if (m_Widget != nullptr)
	{
		m_Widget->Draw();
		if (ImGui::IsItemHovered(m_DelayFlag | ImGuiHoveredFlags_NoSharedDelay))
		{
			ImGui::SetTooltip(m_Text.c_str());
		}
	}
}
