#include "../../dsa_pch.h"

#include "Panel.h"
#include "Logger/Logger.h"

Panel::Panel(std::string id)
{
	m_Id = id;
	m_DrawId = "##" + id;
	m_Children.reserve(16); // 16 widgets should be enough for 1 panel
}

Panel::Panel(std::string id, std::vector<Widget*>& widgets)
{
	m_Id = id;
	m_DrawId = "##" + id;
	for (auto it = widgets.begin(); it != widgets.end(); it++)
	{
		if (*it == nullptr)
		{
			LOG_GUI_ERROR("Can't add child widget, widget is null");
			continue;
		}

		addChild((*it)->GetId(), *it);
	}
}

Panel::~Panel()
{
	// TODO: think if this may be a good idea
	for (auto w : m_Children)
	{
		delete w.second;
	}

	m_Children.clear();
}

inline void Panel::drawWidget()
{
	ImGui::SetNextWindowPos(m_Transform.position);
	ImGui::BeginChild(m_DrawId.c_str(), { 0, 0 }, ImGuiChildFlags_Borders);

	for (auto w : m_Children)
	{
		w.second->Draw();
	}

	ImGui::EndChild();
}

void Panel::AddWidget(Widget* widget)
{
	if (widget == nullptr)
	{
		LOG_GUI_ERROR("Can't add child widget, widget is null");
		return;
	}
	
	addChild(widget->GetId(), widget);
}

Widget* Panel::GetWidget(std::string id)
{
	if (m_Children.find(id) == m_Children.end())
	{
		LOG_GUI_ERROR("Can't find '%s', doesn't exist in Panel '%s'", id.c_str(), m_Id.c_str());
		return nullptr;
	}

	return m_Children[id];
}

void Panel::RemoveWidget(std::string id)
{
	auto del = m_Children.find(id);
	
	if (del != m_Children.end())
	{
		m_Children.erase(del);
	}
	else
	{
		LOG_GUI_ERROR("Can't delete '%s', doesn't exist in Panel '%s'", id, m_Id);
	}
}

void Panel::addChild(std::string id, Widget* widget)
{
	if (id == "")
	{
		LOG_GUI_WARN("Widget id is empty");
	}
	if (m_Children.find(id) != m_Children.end())
	{
		LOG_GUI_WARN("Found duplicate widget id '%s' in Panel '%s'", id.c_str(), m_Id.c_str());
	}

	m_Children[id] = widget;
}
