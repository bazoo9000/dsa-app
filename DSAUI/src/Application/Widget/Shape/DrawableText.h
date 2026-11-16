#pragma once

#include "Shape.h"
#include "DrawableShape.h"
#include "../BasicText.h"

class DrawableText : public BasicText, public Shape, public DrawableShape
{
public:
    DrawableText(const std::string& text, ImFont* font = FONT_DEFAULT, ImVec2 pos = {0 , 0});
    ~DrawableText() = default;

public:
    virtual void DrawShape(ImDrawList* drawList) override;
};
