#pragma once

#include "Widget.h"

class TextBox : public Widget
{
public:
	TextBox(std::string id, std::string text = "");
	~TextBox();

public:
	virtual inline void Draw() override;

public:
	void ModifyText(std::string newText) { m_Text = newText; }

private:
	std::string m_Text;
};