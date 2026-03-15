#pragma once

#include "Widget.h"
#include "BasicText.h"

class TextLabel : public Widget, public BasicText
{
public:
	TextLabel(std::string id, std::string text = "", ImFont* font = FONT_DEFAULT);
	virtual ~TextLabel();

protected:
	virtual inline void drawWidget() override;
};