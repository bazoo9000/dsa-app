#pragma once

#include "WidgetDecorator.h"

enum class TooltipDelay
{
	None,
	Short,
	Normal
};

// NOTE! this is a simple tooltip with just text
// TODO: add CustomTooltip that can show widgets instead of just text
class Tooltip : public WidgetDecorator
{
public:
	Tooltip(Widget* widget, std::string text = "");
	~Tooltip() = default;

public:
	void SetDelay(TooltipDelay delay);
	std::string GetText() { return m_Text; }
	void SetText(std::string text) { m_Text = text; }

protected:
	virtual inline void drawWidget() override;

private:
	ImGuiHoveredFlags m_DelayFlag;
	std::string m_Text;
};