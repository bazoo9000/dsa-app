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
