#pragma once

#include "Widget.h"
#include "Shape/DrawableShape.h"

class Canvas : public Widget
{
public:
	Canvas(std::string id, ImU32 bgColor = IM_COL32_WHITE);
	~Canvas();

public:
	ImU32 GetBgColor() { return m_BgColor; }
	void SetBgColor(ImU32 bgColor) { m_BgColor = bgColor; }
	void AddDrawableShape(DrawableShape* shape);

protected:
	virtual inline void drawWidget() override;

private:
	void drawBackground(ImDrawList* list, ImVec2 offset = { 0, 0 });

private:
	std::string m_DrawId = "##"; // for imgui id
	ImU32 m_BgColor;
	std::vector<DrawableShape*> m_Shapes;
};