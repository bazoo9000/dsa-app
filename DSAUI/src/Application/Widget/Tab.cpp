#include "../../dsa_pch.h"

#include "Tab.h"
#include "Logger/Logger.h"

Tab::Tab(std::string id)
{
	m_Id = id;
	m_DrawId = "##" + id;

}

Tab::Tab(std::string id, std::vector<Widget*>& widgets)
{
	m_Id = id;
	m_DrawId = "##" + id;
	for (auto& w : widgets)
	{
		TabData data(w, false, w->GetId());
		addItem(w->GetId(), data);
	}
}

Tab::~Tab()
{
}

inline void Tab::drawWidget()
{
	if (ImGui::BeginTabBar(m_DrawId.c_str(), ImGuiTabBarFlags_Reorderable))
	{
		for (auto& tab : m_TabItems)
		{
			if (tab.second.selected && ImGui::BeginTabItem(tab.second.name.c_str(), &tab.second.selected))
			{
				tab.second.widget->Draw();
				ImGui::EndTabItem();
			}
		}
		ImGui::EndTabBar();
	}
}

void Tab::AddTabItem(Widget* widget, std::string name, bool selected)
{
	if (widget == nullptr)
	{
		LOG_GUI_ERROR("Can't add child widget, widget is null");
		return;
	}

	TabData data(widget, selected, name);

	addItem(widget->GetId(), data);
}

Widget* Tab::GetTabItemWidget(std::string id)
{
	if (!CheckExists(id))
	{
		LOG_GUI_ERROR("Can't find '%s', doesn't exist in Tab '%s'", id.c_str(), m_Id.c_str());
		return nullptr;
	}

	return m_TabItems[id].widget;
}

bool Tab::GetTabItemSelected(std::string id)
{
	if (!CheckExists(id))
	{
		LOG_GUI_ERROR("Can't find '%s', doesn't exist in Tab '%s'", id.c_str(), m_Id.c_str());
		return false;
	}

	return m_TabItems[id].selected;
}

void Tab::SetTabItemSelected(std::string id, bool selected)
{
	if (!CheckExists(id))
	{
		LOG_GUI_ERROR("Can't find '%s', doesn't exist in Tab '%s'", id.c_str(), m_Id.c_str());
	}

	m_TabItems[id].selected = selected;
}

std::string Tab::GetTabItemName(std::string id)
{
	if (!CheckExists(id))
	{
		LOG_GUI_ERROR("Can't find '%s', doesn't exist in Tab '%s'", id.c_str(), m_Id.c_str());
		return "";
	}

	return m_TabItems[id].name;
}

void Tab::RemoveTabItem(std::string id)
{
	auto del = m_TabItems.find(id);

	if (del != m_TabItems.end())
	{
		m_TabItems.erase(del);
	}
	else
	{
		LOG_GUI_ERROR("Can't delete '%s', doesn't exist in Tab '%s'", id, m_Id);
	}
}

// TODO: try to remove this
std::vector<std::string> Tab::GetAllKeys()
{
	if (m_TabItems.empty())
	{
		return {};
	}

	std::vector<std::string> out;
	out.reserve(m_TabItems.size());

	for (auto& item : m_TabItems)
	{
		out.push_back(item.first);
	}

	return out;
}

bool Tab::CheckExists(std::string id)
{
	return (m_TabItems.find(id) != m_TabItems.end());
}

void Tab::addItem(std::string id, TabData data)
{
	if (id == "")
	{
		LOG_GUI_WARN("Widget id is empty");
	}
	if (CheckExists(id))
	{
		LOG_GUI_WARN("Found duplicate tabitem id '%s' in Tab '%s'", id.c_str(), m_Id.c_str());
	}

	m_TabItems[id] = data;
	data.widget->SetParent(this);
}