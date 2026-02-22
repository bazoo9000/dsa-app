#include "../../dsa_pch.h"

#include "Panel.h"
#include "Logger/Logger.h"

Panel::Panel(std::string id)
{
	m_Id = "##" + id;
	m_Children.reserve(16); // 16 widgets should be enough for 1 panel
}

Panel::Panel(std::string id, std::vector<Widget*>& widgets)
{
	m_Id = "##" + id;
	m_Children = std::move(widgets);
}

Panel::~Panel()
{
	for (auto w : m_Children)
	{
		delete w;
	}

	m_Children.clear();
}

inline void Panel::Draw()
{
	ImGui::SetNextWindowPos(m_Transform.position);
	ImGui::BeginChild(m_Id.c_str(), { 0, 0 }, ImGuiChildFlags_Borders);

	for (auto w : m_Children)
	{
		w->Draw();
	}

	ImGui::EndChild();
}

void Panel::AddWidget(Widget* widget)
{
	m_Children.push_back(widget);
}

void Panel::RemoveWidget(std::string id)
{
	// BAD! ill fix it later
	auto it = m_Children.begin();
	for (; it != m_Children.end(); it++)
	{
		if (id == (*it)->GetId())
		{
			break;
		}
	}

	if (it != m_Children.end())
	{
		m_Children.erase(it);
	}
	else
	{
		LOG_GUI_ERROR("Can't delete '%s', doesn't exist in Panel '%s'", id, m_Id);
	}
}
