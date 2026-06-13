#include "../../dsa_pch.h"

#include "Panel.h"
#include "Logger/Logger.h"

Panel::Panel(std::string id)
{
	m_Id = id;
	m_DrawId = "##" + id;
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
	// BIG TODO: convert all raw pointers to shared pointers or implement my own shared pointer

	m_ChildrenList.clear();
	m_ChildrenMap.clear();
}

inline void Panel::drawWidget()
{
	ImGui::BeginChild(m_DrawId.c_str(), m_Transform.scale, m_ChildFlags, m_WindowFlags);

	for (auto w : m_ChildrenList)
	{
		w->Draw();
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

// TODO: make the search to go recursevily through child panels, needs a deeper search
Widget* Panel::GetWidget(std::string id)
{
	if (m_ChildrenMap.find(id) == m_ChildrenMap.end())
	{
		LOG_GUI_ERROR("Can't find '%s', doesn't exist in Panel '%s'", id.c_str(), m_Id.c_str());
		return nullptr;
	}

	return *m_ChildrenMap[id];
}

void Panel::RemoveWidget(std::string id)
{
	auto del = m_ChildrenMap.find(id);
	
	if (del != m_ChildrenMap.end())
	{
		m_ChildrenList.erase((*del).second);
		m_ChildrenMap.erase(del);
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
	if (m_ChildrenMap.find(id) != m_ChildrenMap.end())
	{
		LOG_GUI_WARN("Found duplicate widget id '%s' in Panel '%s'", id.c_str(), m_Id.c_str());
	}

	m_ChildrenMap[id] = m_ChildrenList.insert(m_ChildrenList.end(), widget);
	widget->SetParent(this);
}
