#pragma once

#include "Widget.h"
#include "BasicText.h"

class TextBox : public Widget, public BasicText
{
public:
	TextBox(std::string id, std::string text = "", ImFont* font = FONT_DEFAULT);
	~TextBox();

protected:
	virtual inline void drawWidget() override;
};