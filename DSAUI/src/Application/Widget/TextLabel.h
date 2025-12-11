#pragma once

#include "Widget.h"

class TextLabel : public Widget
{
public:
	TextLabel(std::string id, std::string text = "");
	virtual ~TextLabel();

public:
	virtual inline void Draw() override;

public:
	void ModifyText(std::string newText) { m_Text = newText; }

private:
	std::string m_Text;
};