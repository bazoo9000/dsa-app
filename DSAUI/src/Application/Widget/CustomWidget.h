#pragma once

#include "Widget.h"

// The purpose of this class is mostly for creating a quick widget and test it
// before wrapping it into a class
class CustomWidget : public Widget
{
public:
	CustomWidget(std::string id);
	~CustomWidget();

public:
	void AddCustomScript(std::function<void()> script) { m_CustomScript = script; }

protected:
	virtual inline void drawWidget() override;

private:
	std::function<void()> m_CustomScript;
};