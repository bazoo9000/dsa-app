#include "../../dsa_pch.h"

#include "WidgetCollector.h"
#include "WidgetDecorator.h"
#include "Logger/Logger.h"

void WidgetCollector::AddWidget(Widget* widget)
{
	if (widget == nullptr)
	{
		LOG_GUI_ERROR("Can't add child widget, widget is null");
		return;
	}

	addChild(widget->GetId(), widget);
}

Widget* WidgetCollector::GetWidget(std::string id)
{
	if (m_ChildrenMap.find(id) == m_ChildrenMap.end())
	{
		for (auto w : m_ChildrenList)
		{
			Widget* ret = nullptr;
			if ((ret = tryFindCollector(w, id)) != nullptr) { return ret; }
			else if ((ret = tryFindDecorator(w, id)) != nullptr) { return ret; }
		}

		LOG_GUI_ERROR("Can't find '%s', doesn't exist in '%s'", id.c_str(), m_Id.c_str());
		return nullptr;
	}

	return *m_ChildrenMap[id];
}

void WidgetCollector::RemoveWidget(std::string id)
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

void WidgetCollector::addChild(std::string id, Widget* widget)
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
	widget->SetParent(this); // TODO: handle what happens if widget already had a parent
}

Widget* WidgetCollector::tryFindCollector(Widget* widget, std::string id)
{
	WidgetCollector* ret = dynamic_cast<WidgetCollector*>(widget);

	if (!ret) { return nullptr; }

	return ret->GetWidget(id);
}

Widget* WidgetCollector::tryFindDecorator(Widget* widget, std::string id)
{
	WidgetDecorator* ret = dynamic_cast<WidgetDecorator*>(widget);

	if (!ret) { return nullptr; }

	return (ret->GetWidgetComponent()->GetId() == id) ? ret : nullptr;
}
