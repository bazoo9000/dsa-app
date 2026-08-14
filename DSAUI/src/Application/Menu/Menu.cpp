#include "../../dsa_pch.h"

#include "Menu.h"
#include "Logger/Logger.h"

Menu::Menu(std::string id)
	: m_Id(id)
{
}

Menu::~Menu()
{
	m_Id.clear();
}

void Menu::Draw()
{
	if (m_MainPanel == nullptr)
	{
		LOG_GUI_FATAL("Can't draw menu, main panel is null");
		exit(1);
	}
	m_MainPanel->Draw();
	RunMenu();
}

void Menu::setAllWidgets(std::vector<Widget*> widgets)
{
	//m_MainPanel = new Panel(menuName, widgets);
	m_MainPanel = new Panel("panel_main", widgets);
	m_MainPanel->ScaleTo(MenuAppSignaler::SignalGetWindowSize());
	m_MainPanel->HideScrollBar();
}
