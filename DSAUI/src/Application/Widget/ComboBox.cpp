#include "../../dsa_pch.h"

#include "ComboBox.h"
#include "Logger/Logger.h"

ComboBox::ComboBox(std::string id)
    : m_Selected(0)
{
    m_Id = "##" + id;
    m_Items.reserve(32);
}

ComboBox::ComboBox(std::string id, std::vector<std::string>& items)
    : m_Selected(0)
{
    m_Id = "##" + id;
    m_Items = std::move(items);
}

ComboBox::~ComboBox()
{
    m_Items.clear();
    m_Selected = -1;
}

inline void ComboBox::Draw()
{
    ImGui::SetCursorPos(m_Transform.position);
    ImGui::SetNextItemWidth(m_Transform.scale.x);
    if (ImGui::BeginCombo(m_Id.c_str(), m_Items[m_Selected].c_str()))
    {
        for (int n = 0; n < m_Items.size(); n++)
        {
            const bool is_selected = (m_Selected == n);
            if (ImGui::Selectable(m_Items[n].c_str(), is_selected))
                m_Selected = n;

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
}

void ComboBox::AddItem(std::string item)
{
    m_Items.push_back(item);
}

void ComboBox::RemoveItem(std::string item)
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
        LOG_GUI_ERROR("Can't delete item %s, doesn't exist in ComboBox %s", item, m_Id);
    }
}
