#include "../../dsa_pch.h"

#include "RadioButton.h"
#include "Logger/Logger.h"

RadioButton::RadioButton(std::string id)
	: m_Selected(0)
{
    m_Id = id;
	m_Items.reserve(32);
}

RadioButton::RadioButton(std::string id, std::vector<std::string>& items)
	: m_Selected(0)
{
    m_Id = id;
	m_Items = std::move(items);
}

RadioButton::~RadioButton()
{
	m_Items.clear();
	m_Selected = -1;
}

inline void RadioButton::Draw()
{
    ImVec2 pos = m_Transform.position;
    for (int i = 0; i < m_Items.size(); i++)
    {
        ImGui::SetCursorPos(pos);
        ImGui::RadioButton(m_Items[i].c_str(), &m_Selected, i);
        pos.y += 25.0f;
    }
}

void RadioButton::AddItem(std::string item)
{
	m_Items.push_back(item);
}

void RadioButton::RemoveItem(std::string item)
{
    auto found = m_Items.end();
    for (auto it = m_Items.begin(); it != m_Items.end(); it++)
    {
        if (*it == item)
        {
            found = it;
            break;
        }
    }

    if (found != m_Items.end())
    {
        m_Items.erase(found);
    }
    else
    {
        LOG_GUI_ERROR("Can't delete item %s, doesn't exist in RadioButton %s", item, m_Id);
    }
}