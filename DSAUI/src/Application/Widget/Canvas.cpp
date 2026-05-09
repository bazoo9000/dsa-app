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
	// To make events only occur to only ONE shape
	// TODO: check if there are better ways to do it, for now this works fine
	static InteractableShape* crtShape = nullptr;

	for (auto ishape : m_InteractableShapes)
	{
		if (ishape != nullptr && (crtShape == nullptr || crtShape == ishape))
		{
			MouseAction action = ishape->CheckMouseAction();

			switch (action)
			{
			case MouseAction::Release:
			case MouseAction::None:
				crtShape = nullptr;
				break;
			case MouseAction::Hover:
			case MouseAction::Click:
			case MouseAction::Hold:
				crtShape = ishape;
				break;
			}

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

	m_Shapes.push_back(shape);
	
	InteractableShape* ishape = dynamic_cast<InteractableShape*>(shape);
	m_InteractableShapes.push_back(ishape);
}

void Canvas::drawWidget()
{
	ImGui::BeginChild(m_DrawId.c_str(), m_Transform.scale, ImGuiChildFlags_Borders | ImGuiWindowFlags_NoScrollbar);

	ImDrawList* drawList = ImGui::GetWindowDrawList();

	if (drawList == nullptr)
	{
		LOG_GUI_FATAL("Draw list is null");
		exit(1);
	}

	ImVec2 canvasScreenPos = ImGui::GetCursorScreenPos() - ImGui::GetStyle().WindowPadding;

	drawBackground(drawList, canvasScreenPos);

	for (DrawableShape* shape : m_Shapes)
	{
		Shape* s = dynamic_cast<Shape*>(shape);
		if (s != nullptr)
		{
			s->SetGlobalOrigin(canvasScreenPos);
		}
		shape->DrawShape(drawList);
	}

	ImGui::EndChild();
}

void Canvas::drawBackground(ImDrawList* drawList, ImVec2 screenPos)
{
	// top-left corner (absolute screen position of canvas)
	ImVec2 start = screenPos;
	// bottom-right corner (add the canvas size)
	ImVec2 end = screenPos + m_Transform.scale;

	drawList->AddRectFilled(
		start,
		end,
		m_BgColor
	);
}
