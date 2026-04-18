#include "../../dsa_pch.h"

#include "Canvas.h"
#include "Shape/InteractableShape.h"
#include "Shape/Shape.h"
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

void Canvas::DoInteractions()
{
	for (auto ishape : m_InteractableShapes)
	{
		if (ishape != nullptr)
		{
			MouseAction action = ishape->CheckMouseAction();
			switch (action)
			{
			case MouseAction::None:    ishape->OnNothing(); break;
			case MouseAction::Hover:   ishape->OnHover();   break;
			case MouseAction::Click:   ishape->OnClick();   break;
			case MouseAction::Hold:    ishape->OnHold();    break;
			case MouseAction::Release: ishape->OnRelease(); break;
			}
		}
	}
}

void Canvas::AddDrawableShape(DrawableShape* shape)
{
	if (shape == nullptr)
	{
		LOG_GUI_ERROR("Can't add DrawableShape, it's null");
		return;
	}

	Shape* s = dynamic_cast<Shape*>(shape);
	if (s != nullptr)
	{
		s->SetGlobalOrigin(m_Transform.position);
	}

	m_Shapes.push_back(shape);
	
	InteractableShape* ishape = dynamic_cast<InteractableShape*>(shape);
	m_InteractableShapes.push_back(ishape);
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

	drawBackground(drawList);

	// TODO: add more shapes, and make them interactable
	for (DrawableShape* shape : m_Shapes)
	{
		shape->DrawShape(drawList);
	}

	ImGui::EndChild();
}

void Canvas::drawBackground(ImDrawList* drawList)
{
	// top-left corner position
	ImVec2 start = m_Transform.position;
	// bottom-right corner position
	ImVec2 end = start + m_Transform.scale;

	drawList->AddRectFilled(
		start,
		end,
		m_BgColor
	);
}
