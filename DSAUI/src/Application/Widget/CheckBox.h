#pragma once

#include "Widget.h"

class CheckBox : public Widget
{
public:
	CheckBox(std::string id, std::string label, bool initialVal = false);
	~CheckBox();

public:
	bool GetValue() { return m_Value; }
	std::string GetLabel() { return m_Label; }
	void SetLabel(std::string label) { m_Label = label; }

protected:
	virtual inline void drawWidget() override;

private:
	bool m_Value = false;
	std::string m_Label;
};