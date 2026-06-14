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
