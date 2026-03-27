#include "../../dsa_pch.h"

#include "Canvas.h"
#include "Logger/Logger.h"

Canvas::Canvas(std::string id, ImU32 bgColor)
	: m_BgColor(bgColor)
{
	m_Id = id;
	m_DrawId = "##" + m_Id;
}

Canvas::~Canvas()
{
}

void Canvas::AddDrawableShape(DrawableShape* shape)
{
	if (shape == nullptr)
	{
		LOG_GUI_ERROR("Can't add DrawableShape, it's null");
		return;
	}

	m_Shapes.push_back(shape);
}

void Canvas::drawWidget()
{
	ImGui::SetNextWindowPos(m_Transform.position);
	ImGui::BeginChild(m_DrawId.c_str(), m_Transform.scale, ImGuiChildFlags_Borders);

	ImDrawList* drawList = ImGui::GetWindowDrawList();

	if (drawList == nullptr)
	{
		LOG_GUI_FATAL("Draw list is null");
		exit(1);
	}

	drawBackground(drawList, m_Transform.position);

	// TODO: add more shapes, and make them interactable
	for (DrawableShape* shape : m_Shapes)
	{
		shape->DrawShape(drawList, m_Transform.position);
	}

	ImGui::EndChild();
}

void Canvas::drawBackground(ImDrawList* drawList, ImVec2 offset)
{
	// top-left corner position
	ImVec2 start = offset;
	// bottom-right corner position
	ImVec2 end = start + m_Transform.scale;

	drawList->AddRectFilled(
		start,
		end,
		m_BgColor
	);
}
