#include "../../dsa_pch.h"

#include "TreeNode.h"

#include "Logger/Logger.h"

TreeNode::TreeNode(std::string id, std::string label)
	: m_Label(label)
{
	m_Id = id;
}

TreeNode::TreeNode(std::string id, std::string label, std::vector<Widget*>& widgets)
	: m_Label(label)
{
	m_Id = id;
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

TreeNode::~TreeNode()
{
}

inline void TreeNode::drawWidget()
{
	if (!m_AutoPos)
	{
		ImGui::SetCursorPos(m_Transform.position);
	}
	if (ImGui::TreeNode(m_Label.c_str()))
	{
		ImVec2 pos = m_Transform.position;
		pos = { pos.x + 20, pos.y + 15 };
		for (auto w : m_ChildrenList)
		{
			if (!m_AutoPos)
			{
				// TODO: Have a better way to position this, this is good enough
				// or instead set all as autopos
				w->MoveTo(pos);
				pos = { pos.x, pos.y + 15 };
			}
			w->Draw();
		}
		ImGui::TreePop();
	}
}

void TreeNode::AddWidget(Widget* widget)
{
	if (widget == nullptr)
	{
		LOG_GUI_ERROR("Can't add child widget, widget is null");
		return;
	}

	addChild(widget->GetId(), widget);
}

Widget* TreeNode::GetWidget(std::string id)
{
	if (m_ChildrenMap.find(id) == m_ChildrenMap.end())
	{
		LOG_GUI_ERROR("Can't find '%s', doesn't exist in TreeNode '%s'", id.c_str(), m_Id.c_str());
		return nullptr;
	}

	return *m_ChildrenMap[id];
}

void TreeNode::RemoveWidget(std::string id)
{
	auto del = m_ChildrenMap.find(id);

	if (del != m_ChildrenMap.end())
	{
		m_ChildrenList.erase((*del).second);
		m_ChildrenMap.erase(del);
	}
	else
	{
		LOG_GUI_ERROR("Can't delete '%s', doesn't exist in TreeNode '%s'", id, m_Id);
	}
}

void TreeNode::addChild(std::string id, Widget* widget)
{
	if (id == "")
	{
		LOG_GUI_WARN("Widget id is empty");
	}
	if (m_ChildrenMap.find(id) != m_ChildrenMap.end())
	{
		LOG_GUI_WARN("Found duplicate widget id '%s' in TreeNode '%s'", id.c_str(), m_Id.c_str());
	}

	m_ChildrenMap[id] = m_ChildrenList.insert(m_ChildrenList.end(), widget);
	widget->SetParent(this);
}
