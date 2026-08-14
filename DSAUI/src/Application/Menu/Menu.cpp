#include "../../dsa_pch.h"

#include "Menu.h"
#include "Logger/Logger.h"

IAppReceiver* Menu::m_App = nullptr;

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

void Menu::SetApp(IAppReceiver* app)
{
	m_App = app;
}

void Menu::signalChangeMenu(std::string id)
{
	m_App->ChangeMenu(id);
}

void Menu::signalCloseApp()
{
	m_App->Close();
}

std::unordered_map<std::string, std::string> Menu::signalRequestTokens(std::vector<std::string> tokens)
{
	return m_App->RequestTokens(tokens);
}

ImVec2 Menu::signalGetWindowSize()
{
	return m_App->GetWindowSize();
}

std::string Menu::GetId()
{
	return m_Id;
}

void Menu::setAllWidgets(std::vector<Widget*> widgets)
{
	//m_MainPanel = new Panel(menuName, widgets);
	m_MainPanel = new Panel("panel_main", widgets);
	m_MainPanel->ScaleTo(signalGetWindowSize());
	m_MainPanel->HideScrollBar();
}
